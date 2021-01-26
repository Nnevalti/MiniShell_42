#include "../include/minishell.h"

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

void	handle_error(t_data *data)
{
	printf("error %d\n", data->error->errno);
	if (data->error->errno == QUOTE)
		free(data->command);
	if (data->error->errno == PARSER)
		free_lexer(data);
	if (data->error->value)
		printf("%s\n", data->error->value);
	free(data->error->value);
	data->error->errno = NOERROR;
}
