/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:01:46 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/17 15:01:49 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create an array for env var
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

// Get an env var using it's name
char 	*get_env_var(char **env, char *name)
{
	int		i;
	int		index;

	i = 0;
	while (env[i])
	{
		index = ft_indexof(env[i], '=');
		if (!ft_strncmp(env[i], name, index))
			return (env[i] + index + 1);
		i++;
	}
	return (NULL);
}

// Create a new env var in the array (called in export)
t_bool	set_env_var(char **env, char *name, char *variable)
{
	int		i;
	int		index;

	i = 0;
	while (env[i])
	{
		index = ft_indexof(env[i], '=');
		if (ft_strlen(name) == index && !ft_strncmp(env[i], name, index - 1))
		{
			free(env[i]);
			env[i] = ft_strdup(variable);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
