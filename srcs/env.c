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

char 	*get_env_var(char **env, char *name)
{
	int		i;
	int	index;

	i = 0;
	while (env[i][0] != '_')
	{
		index = ft_indexof(env[i], '=');
		if (!ft_strncmp(env[i], name, index - 1))
			return (env[i] + index + 1);
		i++;
	}
	return (NULL);
}
