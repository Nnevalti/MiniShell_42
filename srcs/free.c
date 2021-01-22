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
// void	free_ast(t_tree *entry)
// {
// 	if (entry->left)
// 	{
// 		free_ast(entry->left);
// 			if (entry->right)
// 				free_ast(entry->right);
// 	}
// 	if (entry->type == COMMAND)
// 	{
// 		free(entry->command);
// 		if (entry->options != NULL)
// 			free_tab_str(entry->options);
// 	}
// 	else if (entry->type == REDIR)
// 		free(entry->file);
// 	free(entry);
// 	return ;
// }
