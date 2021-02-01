/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bsq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 00:58:46 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 00:59:01 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*trim_bsq(char *str)
{
	int		i;
	int		start;
	char	*new_str;
	char	*tmp;

	i = 0;
	start = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '\\')
			new_str = bsq_handle_bslash(str, new_str, &i, &start);
		else if (str[i] == '\"')
			new_str = bsq_handle_dquotes(str, new_str, &i, &start);
		else if (str[i] == '\'')
			new_str = bsq_handle_squotes(str, new_str, &i, &start);
		else
			i++;
	}
	new_str = copy_bsq(new_str, str, start, i);
	return (new_str);
}

void	redir_bsq(t_command *current)
{
	t_redir	*redir;

	redir = current->redir;
	while (redir)
	{
		redir->str = trim_bsq(redir->str);
		redir = redir->next;
	}
	return ;
}

void	handle_bsq(t_command *current, t_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = trim_bsq(current->cmd);
	free(current->cmd);
	current->cmd = tmp;
	if (current->opt_tab)
	{
		while (current->opt_tab[i])
		{
			tmp = trim_bsq(current->opt_tab[i]);
			free(current->opt_tab[i]);
			current->opt_tab[i] = tmp;
			i++;
		}
	}
	if (current->redir)
		redir_bsq(current);
	return ;
}
