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
	while (env[i][0] != '_')
		ft_printf("%s\n", env[i++]);
	ft_printf("%s\n", env[i]);
	return (0);
}
