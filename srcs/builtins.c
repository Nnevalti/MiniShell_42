/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:30:21 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/15 16:48:11 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_env(char **env)
{
	int		i;

	i = 0;
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

void	ft_cd(t_data *data, t_tree *ptr)
{
	if (ptr->options && ptr->options[1])
	{
		printf("Erreur ta mère la pute\n");
		return ;
	}
	else if (!(ptr->options) || ptr->options[0][0] == '~')
	{
		chdir(get_env_var(data->my_env, "HOME"));
	}
	else
		chdir(ptr->options[0]);
	return ;
}

void	ft_echo(t_tree *ptr)
{
	int				i;

	if (!(ft_strcmp(ptr->options[0], "-n")))
		i = 1;
	else
		i = 0;
	while (ptr->options[i])
	{

		if (!(ft_strcmp(ptr->options[i], "$?")))
		{
			printf("%d", EXIT_CODE);
		}
		else
			printf("%s", ptr->options[i]);
		i++;
	}
	if (ft_strcmp(ptr->options[0], "-n"))
		printf("\n");
	return ;
}

void	ft_export(t_data *data, t_tree *ptr)
{
	int		i;
	int		j;
	int		nb_vars;
	char	*name;
	char	**new_env;

	i = 0;
	while (ptr->options[i])
	{
		if (ft_indexof(ptr->options[i], '=') < 0)
		{
			i++;
			continue;
		}
		name = ft_substr(ptr->options[i], 0, ft_indexof(ptr->options[i], '='));
		if (!set_env_var(data->my_env, name, ptr->options[i]))
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
			new_env[j] = ft_strdup(ptr->options[i]);
			new_env[j + 1] = NULL;
			free_tab_str(data->my_env);
			data->my_env = new_env;
		}
		free(name);
		i++;
	}
	return ;
}

void	ft_unset(t_data *data, t_tree *ptr)
{
	int		i;
	int		j;
	int		k;
	int		nb_vars;
	char	**new_env;

	i = 0;
	while (ptr->options[i])
	{
		if (get_env_var(data->my_env, ptr->options[i]))
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
				if (ft_strncmp(data->my_env[j], ptr->options[i], ft_strlen(ptr->options[i])) != 0)
					new_env[k++] = ft_strdup(data->my_env[j]);
				j++;
			}
			new_env[k + 1] = NULL;
			free_tab_str(data->my_env);
			data->my_env = new_env;
		}
		i++;
	}
}
