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

void	ft_cd(t_tree *ptr)
{
	if (ptr->options[1])
	{
		// handle error ?
		return ;
	}
	if (ptr->opt[0])
		chdir(ptr->opt[0]);
	else
		chdir("");
}

void	ft_echo(t_tree *ptr)
{
	int				i;
	t_redirection	**redirections;

	// redirections = set_redirections(command);
	i = 0;
	while (ptr->options[i])
	{
		if (ft_strcmp(ptr->options[i], "$?"))
		{
				printf("%d", EXIT_CODE);

		}
		else
			printf("%s ", ptr->options[i]);
		i++;
	}
	if (ft_strcmp(ptr->options[0], "-n"))
		printf("\n");
	// reset_redirections(redirections);
}

void	ft_export(char ***env, char **splitted)
{
	int		i;
	int		j;
	int		nb_vars;
	char	*name;
	char	**new_env;

	i = 1;
	while (splitted[i])
	{
		if (ft_indexof(splitted[i], '=') < 0)
		{
			i++;
			continue;
		}
		name = ft_substr(splitted[i], 0, ft_indexof(splitted[i], '='));
		if (!set_env_var(*env, name, splitted[i]))
		{
			nb_vars = 0;
			while ((*env)[nb_vars])
				nb_vars++;
			if (!(new_env = malloc((nb_vars + 2) * sizeof(char *))))
				return ;
			j = 0;
			while (j < nb_vars)
			{
				new_env[j] = ft_strdup((*env)[j]);
				j++;
			}
			new_env[j] = ft_strdup(splitted[i]);
			new_env[j + 1] = NULL;
			free_tab_str(*env);
			*env = new_env;
		}
		free(name);
		i++;
	}
}

void	ft_unset(char ***env, char **splitted)
{
	int		i;
	int		j;
	int		k;
	int		nb_vars;
	char	**new_env;

	i = 1;
	while (splitted[i])
	{
		if (get_env_var(*env, splitted[i]))
		{
			nb_vars = 0;
			while ((*env)[nb_vars])
				nb_vars++;
			if (!(new_env = malloc(nb_vars * sizeof(char *))))
				return ;
			j = 0;
			k = 0;
			while (j < nb_vars)
			{
				if (ft_strncmp((*env)[j], splitted[i], ft_strlen(splitted[i])) != 0)
					new_env[k++] = ft_strdup((*env)[j]);

				j++;
			}
			new_env[k + 1] = NULL;
			free_tab_str(*env);
			*env = new_env;
		}
		i++;
	}
}
