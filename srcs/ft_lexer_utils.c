/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 02:21:27 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 02:21:36 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		skip_quotes(char const *str, int i)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
		{
			if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
				i += 2;
			else
				i++;
		}
	}
	else
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i + 1);
}

int		count_command(char *cmd)
{
	int i;
	int nb_cmd;

	i = 0;
	nb_cmd = 1;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i], "\"\'"))
			i = skip_quotes(cmd, i);
		else if (cmd[i] == ';')
		{
			while (ft_isblank(cmd[i]) || cmd[i] == ';')
				i++;
			if (cmd[i])
				nb_cmd++;
		}
		else
			i++;
	}
	return (nb_cmd);
}

int		find_start(char *cmd, int i, char *sep)
{
	while (cmd && (ft_search(cmd[i], sep)))
		i++;
	while (cmd && ft_isblank(cmd[i]))
		i++;
	return (i);
}

int		find_end(char *cmd, int i, char *sep)
{
	int		j;

	j = 0;
	if (ft_search(cmd[i], sep) || cmd[i] == '\0')
		j++;
	while (cmd && ft_isblank(cmd[i - j]))
		j++;
	return ((i - j) + 1);
}
