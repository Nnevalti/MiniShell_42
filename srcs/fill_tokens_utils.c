/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 03:56:22 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 03:56:27 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fill_tokens_utils_return(char *cmd, int *start, int *i)
{
	char *tokens;

	if (!(ft_strncmp(&cmd[(*i)], ">>", 2)))
	{
		tokens = ft_substr(cmd, (*start), find_end(cmd, (*i), ">")
			- (*start));
		(*start) = (*i);
		(*i) += 2;
	}
	else
	{
		tokens = ft_substr(cmd, (*start), find_end(cmd, (*i), ">")
			- (*start));
		(*start) = (*i);
		(*i)++;
	}
	return (tokens);
}

char	*fill_tokens_utils(char *cmd, int *start, int *i)
{
	char *tokens;

	if (cmd[(*i)] == '\\')
		(*i) += 2;
	else if (ft_search(cmd[(*i)], "\"\'"))
		(*i) = skip_quotes(cmd, (*i));
	else if (cmd[(*i)] == '>')
	{
		return (fill_tokens_utils_return(cmd, start, i));
	}
	else if (ft_search(cmd[(*i)], "|<"))
	{
		tokens = ft_substr(cmd, (*start), find_end(cmd, (*i), "|<")
			- (*start));
		(*start) = (*i);
		(*i)++;
		return (tokens);
	}
	else
		(*i)++;
	return (NULL);
}
