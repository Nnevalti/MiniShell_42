/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:05:15 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:05:16 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		check_empty_command(t_data *data, char *command)
{
	int		i;

	i = 0;
	while (command && ft_isblank(command[i]))
		i++;
	if (command[i] == '\0')
	{
		free(command);
		return (-1);
	}
	return (0);
}

int		check_syntax_error(t_data *data, char *command)
{
	char	*tmp;

	if (command[0] == '|' || command[0] == ';')
	{
		tmp = ft_strdup("Minishell: syntax error near unexpected token ");
		data->error->errtype = SYNTAX;
		data->error->value = ft_strnjoin(tmp, command, 1);
		free(tmp);
		errno = 2;
		return (-1);
	}
	return (0);
}

void	handle_error(t_data *data)
{
	if (data->error->errtype == QUOTE)
		free(data->command);
	if (data->error->errtype == PARSER)
		free_lexer(data);
	if (data->error->value)
	{
		ft_putstr_fd(data->error->value, 2);
		ft_putstr_fd("\n", 2);
		free(data->error->value);
		data->error->value = NULL;
	}
	data->error->errtype = NOERROR;
}

int		check_command(t_data *data)
{
	if (check_empty_command(data, data->command) == -1
	|| check_quotes_error(data, data->command) == -1
	|| check_semicolons_error(data, data->command) == -1
	|| check_syntax_error(data, data->command) == -1)
		return (-1);
	return (0);
}
