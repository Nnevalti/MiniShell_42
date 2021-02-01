/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:04:09 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:04:12 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	preexecutor(t_command *current, t_data *data)
{
	handle_env(current, data);
	create_opt_tab(current, data);
	handle_bsq(current, data);
	return ;
}

int		set_empty_opt_tab(t_command *current)
{
	char	**tmp;

	if (current->opt_tab)
	{
		tmp = prepend_str(current->cmd, current->opt_tab);
		free_tab_str(current->opt_tab);
		current->opt_tab = tmp;
	}
	else
	{
		if (!(current->opt_tab = malloc(sizeof(char *) * 2)))
			return (-1);
		current->opt_tab[0] = ft_strdup(current->cmd);
		current->opt_tab[1] = NULL;
	}
	return (0);
}

void	exec_and_reset_redir(t_data *data, t_command *current)
{
	exec_cmd(data, current);
	if (current->redir)
		reset_redir(current->last_stdin, current->last_stdout);
	return ;
}

void	analyse_parser(t_command *cmd, t_data *data)
{
	t_command	*current;

	current = cmd;
	while (current)
	{
		preexecutor(current, data);
		if (set_empty_opt_tab(current) == -1)
			return ;
		if (current->redir)
			handle_redir(data, current, current->redir);
		if (current->pipe)
			handle_pipes(data, current, current->pipe);
		if (data->error->errtype == NOERROR)
			exec_and_reset_redir(data, current);
		else
		{
			handle_error(data);
			return ;
		}
		current = current->next;
	}
	return ;
}

void	ft_executor(t_data *data)
{
	int i;

	i = 0;
	while (data->parser[i])
	{
		analyse_parser(data->parser[i], data);
		i++;
	}
}
