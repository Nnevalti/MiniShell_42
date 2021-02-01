/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:32:08 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 19:32:10 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		skip_sc_err_bs(char *command, int i)
{
	if (command[i] == '\\')
		i += 2;
	return (i);
}

int		skip_sc_bsq(char *command, int i)
{
	i = skip_sc_err_sq(command, i);
	i = skip_sc_err_dq(command, i);
	i = skip_sc_err_bs(command, i);
	return (i);
}

int		check_semicolons_error(t_data *data, char *command)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	while (command[i])
	{
		i = skip_sc_bsq(command, i);
		if (command[i] == ';' || command[i] == '|')
		{
			j = i - 1;
			while (j > 0 && command[j] && ft_isblank(command[j]))
				j--;
			if (j == start)
			{
				set_sc_error(data, command, i);
				errno = 2;
				return (-1);
			}
			start = i;
		}
		i++;
	}
	return (0);
}

int		check_quotes_error(t_data *data, char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\\' && command[i + 1])
			i += 2;
		if (command[i] == '\'')
		{
			i = check_missquotes(command, i);
			if (command[i] == '\0')
				return (set_q_error(data));
		}
		else if (command[i] == '\"')
		{
			i = check_missquotes(command, i);
			if (command[i] == '\0')
				return (set_q_error(data));
		}
		i++;
	}
	return (0);
}

int		check_error(t_data *data, char ***tokens)
{
	int		i;
	int		j;
	char	*t;

	i = 0;
	while (tokens && tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (!ft_strcmp(tokens[i][j], "|") || !ft_strcmp(tokens[i][j], ">>")
			|| !ft_strcmp(tokens[i][j], ">") || !ft_strcmp(tokens[i][j], "<"))
			{
				t = ft_strdup("Minishell: syntax error near unexpected token ");
				data->error->errtype = PARSER;
				data->error->value = ft_strjoin(t, tokens[i][j]);
				free(t);
				errno = 2;
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
