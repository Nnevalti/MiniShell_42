/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:03:45 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:03:49 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab_str(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return ;
}

void	free_lexer(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		free_tab_str(data->tokens[i]);
		i++;
	}
	free(data->tokens);
}

void	free_redir(t_redir *redir)
{
	if (redir->str)
		free(redir->str);
	if (redir->next)
		free_redir(redir->next);
	free(redir);
	return ;
}

void	free_recursif(t_command *ptr)
{
	if (ptr)
	{
		if (ptr->cmd)
			free(ptr->cmd);
		if (ptr->opt)
			free(ptr->opt);
		if (ptr->opt_tab)
			free_tab_str(ptr->opt_tab);
		if (ptr->redir)
			free_redir(ptr->redir);
		if (ptr->pipe)
			free(ptr->pipe);
	}
	if (ptr->next)
		free_recursif(ptr->next);
	free(ptr);
	return ;
}

void	free_parser(t_command **parser)
{
	int			i;
	t_command	*current;

	i = 0;
	while (parser[i])
	{
		free_recursif(parser[i]);
		i++;
	}
	free(parser);
	return ;
}
