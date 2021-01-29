#include "../include/minishell.h"

int		check_semicolons_error(t_data *data, char *command)
{
	int i;
	int j;
	int start;
	char	*tmp;

	i = 0;
	start = 0;
	while (command[i])
	{
		if (command[i] == ';' || command[i] == '|')
		{
			j = i - 1;
			while (ft_isblank(command[j]) && j > 0)
				j--;
			if (j == start)
			{
				tmp = ft_strdup("Minishell: syntax error near ");
				data->error->errno = SYNTAX;
				data->error->value = ft_strnjoin(tmp, &command[i], 1);
				free(tmp);
				return (-1);
			}
			start = i;
		}
		i++;
	}
	return(0);
}

int		check_quotes_error(t_data *data, char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\\' && command[i + 1])
			i += 2;
		else if (command[i] == '\'')
		{
			i++;
			while (command[i] && command[i] != '\'')
				i++;
			if (command[i] == '\0')
			{
				data->error->value = ft_strdup("Minishell: quote error");
				data->error->errno = QUOTE;
				return (-1);
			}
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
			if (command[i] == '\0')
			{
				data->error->value = ft_strdup("Minishell: quote error");
				data->error->errno = QUOTE;
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int		check_error(t_data *data, char ***tokens)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tokens && tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (!ft_strcmp(tokens[i][j], "|") || !ft_strcmp(tokens[i][j], ">>")
			|| !ft_strcmp(tokens[i][j], ">") || !ft_strcmp(tokens[i][j], "<"))
			{
				tmp = ft_strdup("Minishell: parse error near ");
				data->error->errno = PARSER;
				data->error->value = ft_strjoin(tmp, tokens[i][j]);
				free(tmp);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		check_empty_command(t_data *data, char *command)
{
	int		i;

	i = 0;
	while (ft_isblank(command[i]))
		i++;
	if (command[i] == '\0')
		return (-1);
	return (0);
}

int		check_syntax_error(t_data *data, char *command)
{
	char	*tmp;

	if (command[0] == '|' || command[0] == ';')
	{
		tmp = ft_strdup("Minishell: syntax error near ");
		data->error->errno = SYNTAX;
		data->error->value = ft_strnjoin(tmp, command, 1);
		free(tmp);
		return (-1);
	}
	return (0);
}

void	handle_error(t_data *data)
{
	if (data->error->errno == QUOTE)
		free(data->command);
	if (data->error->errno == PARSER)
		free_lexer(data);
	if (data->error->value)
	{
		ft_putstr_fd(data->error->value, 2);
		ft_putstr_fd("\n", 2);
		free(data->error->value);
		data->error->value = NULL;
	}
	data->error->errno = NOERROR;
}
