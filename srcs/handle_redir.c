/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:05:37 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:05:39 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_redir(t_redir *stdin, t_redir *stdout)
{
	if (stdout)
	{
		dup2(stdout->saved_fd, 1);
		close(stdout->saved_fd);
	}
	if (stdin)
	{
		dup2(stdin->saved_fd, 0);
		close(stdin->saved_fd);
	}
	return ;
}

void	handle_bad_fd(t_data *data, char *str)
{
	char *tmp;

	tmp = ft_strdup("Minishell: no such file or directory: ");
	data->error->value = ft_strjoin(tmp, str);
	data->error->errtype = FD;
	errno = 1;
	free(tmp);
}

void	set_redir(t_data *data, t_redir *stdin, t_redir *stdout)
{
	int		fd;

	if (stdout && (stdout->type == REDIRECT_STDOUT
		|| stdout->type == APPEND_STDOUT))
	{
		stdout->saved_fd = dup(1);
		dup2(stdout->fd, 1);
		close(stdout->fd);
	}
	if (stdin && stdin->type == REDIRECT_STDIN)
	{
		stdin->saved_fd = dup(0);
		dup2(stdin->fd, 0);
		close(stdin->fd);
	}
	return ;
}

int		create_file(t_data *data, t_redir *r)
{
	if (r->type == REDIRECT_STDOUT)
	{
		if ((r->fd = open(r->str, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
		{
			handle_bad_fd(data, r->str);
			return (-1);
		}
	}
	else if (r->type == APPEND_STDOUT)
	{
		if ((r->fd = open(r->str, O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
		{
			handle_bad_fd(data, r->str);
			return (-1);
		}
	}
	else if (r->type == REDIRECT_STDIN)
	{
		if ((r->fd = open(r->str, O_RDONLY, 0777)) == -1)
		{
			handle_bad_fd(data, r->str);
			return (-1);
		}
	}
	return (0);
}

void	handle_redir(t_data *data, t_command *cmd, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIRECT_STDOUT || redir->type == APPEND_STDOUT)
		{
			if (create_file(data, redir) == -1)
				return ;
			cmd->last_stdout = redir;
		}
		if (redir->type == REDIRECT_STDIN)
		{
			if (create_file(data, redir) == -1)
				return ;
			cmd->last_stdin = redir;
		}
		redir = redir->next;
	}
	set_redir(data, cmd->last_stdin, cmd->last_stdout);
	return ;
}
