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

#include "minishell.h"

int		ft_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
	return (0);
}

void ft_pwd(char **env)
{
	char	buffer[4096];

	getcwd(buffer, 4096);
	ft_printf("%s\n", buffer);
}

void	ft_echo(char** splitted)
{
	int	i;

	i = 1;
	while (splitted[i])
	{
		if (ft_strcmp(splitted[i], "-n"))
			ft_printf("%s ", splitted[i]);
		i++;
	}
	if (ft_strcmp(splitted[1], "-n"))
		ft_printf("\n");
}
