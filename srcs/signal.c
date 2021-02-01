/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:06:26 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:06:27 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	kill_prg(int sig)
{
	(void)sig;
	if (g_pid[0] != 0 && g_pid[1] == 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		kill(g_pid[0], SIGQUIT);
		errno = 131;
	}
	else if (g_pid[1] != 0)
	{
		kill(g_pid[1], SIGINT);
		errno = 131;
	}
	else
		ft_putstr_fd("\b \b\b \b", 2);
}

void	signal_handler(int sig)
{
	(void)sig;
	if (g_pid[0] == 0 && g_pid[1] == 0)
	{
		ft_putstr_fd("\n", 2);
		prompt();
	}
	else
	{
		if (g_pid[1] != 0)
			kill(g_pid[1], SIGINT);
		else
			kill(g_pid[0], SIGINT);
		write(1, "\n", 1);
	}
	errno = 130;
}
