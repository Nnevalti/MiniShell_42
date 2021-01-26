/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:00:05 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/15 16:47:56 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html
*/

int 	*init_pipes(char **tokens)
{
	int		*pipes;
	int		i;

	pipes = ft_calloc((tab_str_len(tokens) - 1) * 2 + 1, sizeof(int));
	i = 0;
	while (i < (tab_str_len(tokens) - 1) * 2)
	{
		pipe(pipes + i);
		i += 2;
	}
	return (pipes);
}


void	pipe_io(int *pipes, int index)
{
	if (index > 0)
	{
		printf("dup2(pipes[%d], 0);\n", 2 * (index - 1));
		dup2(pipes[2 * (index - 1)], 0);
	}
	if (pipes[2 * index + 1])
	{
		printf("dup2(pipes[%d], 1);\n", 2 * index + 1);
		dup2(pipes[2 * index + 1], 1);

	}
	close_pipes(pipes);
}

void	close_pipes(int *pipes)
{
	int		i;

	i = 0;
	while (pipes[i])
		close(pipes[i++]);
}
