/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bsq_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:47:26 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 20:47:27 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*copy_bsq2(char *new_str, char *str, int start, int i)
{
	char *tmp;

	if (!new_str)
		new_str = ft_substr(str, start, i - start);
	else
	{
		tmp = ft_strnjoin(new_str, &str[start], i - start);
		free(new_str);
		new_str = tmp;
	}
	return (new_str);
}

char	*copy_bsq(char *new_str, char *str, int start, int i)
{
	char *tmp;

	if (!new_str)
		new_str = ft_substr(str, start, i);
	else
	{
		tmp = ft_strnjoin(new_str, &str[start], i - start);
		free(new_str);
		new_str = tmp;
	}
	return (new_str);
}

char	*bsq_handle_bslash(char *str, char *new_str, int *i, int *start)
{
	new_str = copy_bsq(new_str, str, (*start), (*i));
	(*i)++;
	(*start) = (*i);
	(*i)++;
	return (new_str);
}

char	*bsq_handle_dquotes(char *str, char *new_str, int *i, int *start)
{
	new_str = copy_bsq(new_str, str, (*start), (*i));
	(*i)++;
	(*start) = (*i);
	while (str[(*i)] && str[(*i)] != '\"')
	{
		if (str[(*i)] == '\\')
		{
			if (ft_search(str[(*i) + 1], "\\$\""))
			{
				new_str = copy_bsq(new_str, str, (*start), (*i));
				(*i)++;
				(*start) = (*i);
				(*i)++;
			}
			else
				(*i) += 2;
		}
		else
			(*i)++;
	}
	new_str = copy_bsq2(new_str, str, (*start), (*i));
	(*i)++;
	(*start) = (*i);
	return (new_str);
}

char	*bsq_handle_squotes(char *str, char *new_str, int *i, int *start)
{
	new_str = copy_bsq(new_str, str, (*start), (*i));
	(*i)++;
	(*start) = (*i);
	while (str[(*i)] != '\'')
		(*i)++;
	new_str = copy_bsq(new_str, str, (*start), (*i));
	(*i)++;
	(*start) = (*i);
	return (new_str);
}
