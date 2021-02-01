/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_piperedir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:47:42 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 14:47:44 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe		*ft_init_pipe(void)
{
	t_pipe	*pipe;

	if (!(pipe = (t_pipe *)malloc(sizeof(t_pipe))))
		return (NULL);
	pipe->in = FALSE;
	pipe->out = FALSE;
	pipe->stdin[0] = 0;
	pipe->stdin[1] = 0;
	pipe->stdout[0] = 0;
	pipe->stdout[1] = 0;
	return (pipe);
}

t_redir		*ft_init_redir(void)
{
	t_redir	*redir;

	if (!(redir = (t_redir *)malloc(sizeof(t_redir))))
		return (NULL);
	redir->str = NULL;
	redir->type = NONE;
	redir->saved_fd = 0;
	redir->fd = 0;
	redir->next = NULL;
	return (redir);
}

void		init_pipe_out(t_command *ptr)
{
	if (!(ptr->pipe))
		ptr->pipe = ft_init_pipe();
	ptr->pipe->out = TRUE;
}

void		init_pipe_in(t_command *ptr)
{
	if (!(ptr->pipe))
		ptr->pipe = ft_init_pipe();
	ptr->pipe->in = TRUE;
}
