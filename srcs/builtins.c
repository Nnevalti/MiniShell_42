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

void	ft_pwd(void)
{
	char	buffer[MAX_PATH_LENGTH];

	getcwd(buffer, MAX_PATH_LENGTH);
	printf("%s\n", buffer);
}

void	ft_setpwd(char *pwd, char *oldpwd, t_data *data, char *buffer)
{
	pwd = ft_strjoin("PWD=", getcwd(buffer, MAX_PATH_LENGTH));
	set_env_var(data->my_env, "PWD", pwd);
	set_env_var(data->my_env, "OLDPWD", oldpwd);
	free(pwd);
	free(oldpwd);
	return ;
}

int		ft_exec_cd(t_command *ptr, char *oldpwd)
{
	if (chdir(ptr->opt_tab[1]) == -1)
	{
		free(oldpwd);
		ft_puterror("Minishell: cd: ", ptr->opt_tab[1],
			": Not a directory\n");
		errno = 1;
		return (-1);
	}
	return (0);
}

void	ft_cd(t_data *data, t_command *ptr)
{
	char	*name;
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
	if (tab_str_len(ptr->opt_tab) == 1 || (tab_str_len(ptr->opt_tab) == 2
				&& !ft_strcmp(ptr->opt_tab[1], "~")))
		chdir(get_env_var(data->my_env, "HOME"));
	else if (!ft_strcmp(ptr->opt_tab[1], "-"))
		chdir(get_env_var(data->my_env, "OLDPWD"));
	else if (ft_exec_cd(ptr, oldpwd) == -1)
		return ;
	ft_setpwd(pwd, oldpwd, data, buffer);
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
		ft_putstr_fd(ptr->opt_tab[i], 1);
		if (i < (tab_str_len(ptr->opt_tab) - 1))
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (tab_str_len(ptr->opt_tab) == 1 || (tab_str_len(ptr->opt_tab) >= 2
		&& ft_strcmp(ptr->opt_tab[1], "-n")))
		ft_putstr_fd("\n", 1);
	return ;
}
