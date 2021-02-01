/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:41:24 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 14:41:26 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			ft_set_redir_utils(char *token, t_redir *redir, t_redir_type type)
{
	int i;
	int j;

	i = 0;
	while (token[i] && ft_isblank(token[i]))
		i++;
	j = 0;
	while (!(ft_isblank(token[i + j])) && token[i + j] != '\0')
		j++;
	redir->str = ft_substr(token, i, j);
	redir->type = type;
	i = i + j;
	while (token[i] && ft_isblank(token[i]))
		i++;
	return (i);
}

t_command	*ft_create_struct(char *tokens)
{
	t_command	*ptr;
	int			i;

	i = 0;
	ptr = ft_init_command();
	while (tokens[i])
	{
		if (ft_isblank(tokens[i]))
		{
			ptr->cmd = ft_substr(tokens, 0, i);
			while (ft_isblank(tokens[i]))
				i++;
			if (tokens[i] == '\0')
				return (ptr);
			else
			{
				ptr->opt = ft_substr(tokens, i, ft_strlen(&tokens[i]));
				return (ptr);
			}
		}
		i++;
	}
	ptr->cmd = ft_strdup(tokens);
	return (ptr);
}

int			multiple_commands(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	if (i > 1)
		return (1);
	return (0);
}
