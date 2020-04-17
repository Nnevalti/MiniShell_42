/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:00:05 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/15 16:47:56 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **env)
{
	char	buffer[4096];

	getcwd(buffer, 4096);
	ft_printf("\e[1m\e[32m");
	ft_printf("%s@minishell:", get_env_var(env, "USERNAME"));
	ft_printf("\e[94m%s \e[39m$> \e[0m", buffer);
}

int		main(int argc, char **argv, char **env)
{
	int		i;
	char	*command;
	char 	**splitted;

	// signal(SIGINT, SIG_IGN);
	while (42)
	{
		prompt(env);
		get_next_line(0, &command);
		splitted = ft_split(command, ' ');
		// parser la commande par rapport au espacccce et vérifier avec strcmp ?
		if (!ft_strcmp(splitted[0], "echo"))
		{
			i = 1;
			while (splitted[i])
				ft_printf("%s ", splitted[i++]);
			ft_printf("\n");
		}
		else if (!ft_strcmp(splitted[0], "env"))
			ft_env(env);
		else if (!ft_strcmp(splitted[0], "exit"))
			exit(0);
		free(command);
		i = 0;
		while (splitted[i])
			free(splitted[i++]);
		free(splitted);
	}
}
