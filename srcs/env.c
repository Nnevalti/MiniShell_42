/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:03:26 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:03:28 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **env)
{
	int		nb_vars;
	int		i;
	char	**my_env;

	nb_vars = 0;
	while (env[nb_vars])
		nb_vars++;
	if (!(my_env = malloc((nb_vars + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < nb_vars)
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

char	*get_env_var(char **env, char *name)
{
	int		i;
	int		index;

	i = 0;
	while (env[i])
	{
		index = ft_indexof(env[i], '=');
		if (ft_strlen(name) == index && !ft_strncmp(env[i], name, index))
			return (env[i] + index + 1);
		i++;
	}
	return (NULL);
}

t_bool	set_env_var(char **env, char *name, char *variable)
{
	int		i;
	int		index;

	i = 0;
	while (env[i])
	{
		index = ft_indexof(env[i], '=');
		if (ft_strlen(name) == index && !ft_strncmp(env[i], name, index))
		{
			free(env[i]);
			env[i] = ft_strdup(variable);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
