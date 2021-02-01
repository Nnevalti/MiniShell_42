/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:27:42 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 19:27:54 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		skip_sc_err_q(char *command, int i)
{
	if (command[i] == '\'')
	{
		i++;
		while (command[i] != '\'')
			i++;
		i++;
	}
	return (i);
}

void	set_sc_error(t_data *data, char *command, int i)
{
	char	*tmp;

	tmp = ft_strdup("Minishell: syntax error near unexpected token ");
	data->error->errtype = SYNTAX;
	data->error->value = ft_strnjoin(tmp, &command[i], 1);
	free(tmp);
}

int		check_missquotes(char *command, int i)
{
	if (command[i] == '\'')
	{
		i++;
		while (command[i] && command[i] != '\'')
			i++;
	}
	else if (command[i] == '\"')
	{
		i++;
		while (command[i] && command[i] != '\"')
		{
			if (command[i] == '\\' && command[i + 1])
				i += 2;
			else
				i++;
		}
	}
	return (i);
}

int		set_q_error(t_data *data)
{
	data->error->value = ft_strdup("Minishell: quote error");
	data->error->errtype = QUOTE;
	errno = 2;
	return (-1);
}
