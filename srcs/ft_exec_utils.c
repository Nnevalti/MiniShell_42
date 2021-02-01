/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:07:51 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 20:07:55 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_pipe(t_command *cmd)
{
	if (cmd->p_handled && cmd->pipe->in && !cmd->last_stdin)
	{
		close(cmd->pipe->stdin[1]);
		dup2(cmd->pipe->stdin[0], 0);
	}
	if (cmd->p_handled && cmd->pipe->out && !cmd->last_stdout)
	{
		close(cmd->pipe->stdout[0]);
		dup2(cmd->pipe->stdout[1], 1);
	}
	return ;
}

void	close_pipe(t_command *cmd)
{
	if (cmd->p_handled && cmd->pipe->in)
	{
		close(cmd->pipe->stdin[0]);
		close(cmd->pipe->stdin[1]);
	}
	if (cmd->p_handled && cmd->pipe->out)
	{
		close(cmd->pipe->stdout[1]);
		close(cmd->pipe->stdout[0]);
	}
	return ;
}
