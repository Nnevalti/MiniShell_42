#include "../include/minishell.h"

int	check_error(t_data *data, char ***tokens)
{
	int 	i;
	int		j;
	char	*tmp;

	i = 0;
	while (tokens && tokens[i])
	{
		j = 0;
		while(tokens[i][j])
		{
			if (!ft_strcmp(tokens[i][j], "|") || !ft_strcmp(tokens[i][j], ">>")
			|| !ft_strcmp(tokens[i][j], ">") || !ft_strcmp(tokens[i][j], "<"))
			{
				tmp = ft_strdup("Minishell: parse error near ");
				data->error->errno = PARSER;
				data->error->value = ft_strjoin(tmp, tokens[i][j]);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return(0);
}


void 	handle_error(t_data *data)
{
	printf("error %d\n", data->error->errno);
	// if (data->error->errno == QUOTE)
	// {
	// 	free(data->command);
	// }
	if (data->error->errno == PARSER)
	{
		printf("nani the fuck ?\n");
		// free(data->command);
		free_lexer(data);
	}
	if (data->error->value)
		printf("%s\n", data->error->value);
	free(data->error->value);
	data->error->errno = NOERROR;
}
