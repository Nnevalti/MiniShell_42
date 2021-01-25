/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:00:05 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/15 16:47:56 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab_str(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return ;
}

void	free_tokens(char ***tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		free_tab_str(tokens[i]);
		i++;
	}
	free(tokens);
	return ;
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
		if(ptr->cmd)
			free(ptr->cmd);
		if(ptr->opt)
			free(ptr->opt);
		if(ptr->redir)
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
	int i;
	t_command *current;

	i = 0;
	while(parser[i])
	{
		free_recursif(parser[i]);
		i++;
	}
	free(parser);
	return ;
}
