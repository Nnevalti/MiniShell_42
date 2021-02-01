/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:03:10 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:03:16 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_env(t_command *cmd, char **env)
{
	int		i;

	i = 0;
	if (cmd && cmd->opt_tab && (tab_str_len(cmd->opt_tab) > 1))
	{
		errno = 1;
		return (1);
	}
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}

void	ft_pwd(void)
{
	char	buffer[MAX_PATH_LENGTH];

	getcwd(buffer, MAX_PATH_LENGTH);
	printf("%s\n", buffer);
}

void	ft_cd(t_data *data, t_command *ptr)
{
	char	*name;
	char	*tmp;
	char	*oldpwd;
	char	*pwd;
	char	buffer[MAX_PATH_LENGTH];

	if (ptr->opt_tab && (tab_str_len(ptr->opt_tab) > 2))
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		errno = 1;
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", getcwd(buffer, MAX_PATH_LENGTH));
	if (tab_str_len(ptr->opt_tab) == 1
				|| (tab_str_len(ptr->opt_tab) == 2
				&& !ft_strcmp(ptr->opt_tab[1], "~")))
	{
		chdir(get_env_var(data->my_env, "HOME"));
	}
	else if (!ft_strcmp(ptr->opt_tab[1], "-"))
	{
		chdir(get_env_var(data->my_env, "OLDPWD"));
	}
	else
	{
		if (chdir(ptr->opt_tab[1]) == -1)
		{
			free(oldpwd);
			tmp = ft_strjoin("Minishell: cd: ", ptr->opt_tab[1]);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd(": Not a directory\n", 2);
			free(tmp);
			errno = 1;
			return ;
		}
	}
	pwd = ft_strjoin("PWD=", getcwd(buffer, MAX_PATH_LENGTH));
	set_env_var(data->my_env, "PWD", pwd);
	set_env_var(data->my_env, "OLDPWD", oldpwd);
	free(pwd);
	free(oldpwd);
	return ;
}

void	ft_echo(t_command *ptr)
{
	int				i;
	int				j;

	if ((tab_str_len(ptr->opt_tab) >= 2)
		&& !(ft_strcmp(ptr->opt_tab[1], "-n")))
		i = 2;
	else
		i = 1;
	while (ptr->opt_tab[i])
	{
		// handle $? in a function that replace it by its value
		ft_putstr_fd(ptr->opt_tab[i], 1);
		if (i < (tab_str_len(ptr->opt_tab) - 1))
			ft_putstr_fd(" ", 1);
		i++;
	}
	if ( tab_str_len(ptr->opt_tab) == 1 || (tab_str_len(ptr->opt_tab) >= 2
		&& ft_strcmp(ptr->opt_tab[1], "-n")))
		ft_putstr_fd("\n", 1);
	return ;
}

void	sort_env_array(char **env_array)
{
	int 	i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_array[i])
	{
		j = 1;
		while (env_array[j + i])
		{
			if (ft_strcmp(env_array[j + i], env_array[i]) < 0)
			{
				tmp = env_array[i];
				env_array[i] = env_array[i + j];
				env_array[i + j] = tmp;
			}
			j++;
		}
		i++;
	}
	ft_env(NULL, env_array);
}

void	sort_export(char **env)
{
	char	**sort_env;
	int		i;
	int		j;

	while (env[i + j])
	{
		if (env[i + j][0] == '_')
			j++;
		else
			i++;
	}
	if (!(sort_env = malloc(sizeof(char *) * (i + 1))))
		return ;
	i = 0;
	j = 0;
	while (env[i + j])
	{
		if (env[i + j][0] == '_')
			j++;
		else
		{
			sort_env[i] = ft_strjoin("declare -x ", env[i + j]);
			i++;
		}
	}
	sort_env[i] = NULL;
	sort_env_array(sort_env);
	free_tab_str(sort_env);
	return ;
}
void	ft_export(t_data *data, t_command *ptr)
{
	int		i;
	int		j;
	int		nb_vars;
	char	*name;
	char	**new_env;

	i = 0;
	if (tab_str_len(ptr->opt_tab) == 1)
		sort_export(data->my_env);
	while (ptr->opt_tab[i])
	{
		if (ft_indexof(ptr->opt_tab[i], '=') < 0)
		{
			i++;
			continue;
		}
		name = ft_substr(ptr->opt_tab[i], 0,
					ft_indexof(ptr->opt_tab[i], '='));
		if (!set_env_var(data->my_env, name, ptr->opt_tab[i]))
		{
			nb_vars = 0;
			while (data->my_env[nb_vars])
				nb_vars++;
			if (!(new_env = malloc((nb_vars + 2) * sizeof(char *))))
				return ;
			j = 0;
			while (j < nb_vars)
			{
				new_env[j] = ft_strdup(data->my_env[j]);
				j++;
			}
			new_env[j] = ft_strdup(ptr->opt_tab[i]);
			new_env[j + 1] = NULL;
			free_tab_str(data->my_env);
			data->my_env = new_env;
		}
		free(name);
		i++;
	}
	return ;
}

void	ft_unset(t_data *data, t_command *ptr)
{
	int		i;
	int		j;
	int		k;
	int		nb_vars;
	char	**new_env;

	i = 0;
	while (ptr->opt_tab[i])
	{
		if (get_env_var(data->my_env, ptr->opt_tab[i]))
		{
			nb_vars = 0;
			while (data->my_env[nb_vars])
				nb_vars++;
			if (!(new_env = malloc(nb_vars * sizeof(char *))))
				return ;
			j = 0;
			k = 0;
			while (j < nb_vars)
			{
				if (ft_strncmp(data->my_env[j], ptr->opt_tab[i],
					ft_strlen(ptr->opt_tab[i])) != 0)
				{
					new_env[k] = ft_strdup(data->my_env[j]);
					k++;
				}
				j++;
			}
			new_env[k] = NULL;
			free_tab_str(data->my_env);
			data->my_env = new_env;
		}
		i++;
	}
}
