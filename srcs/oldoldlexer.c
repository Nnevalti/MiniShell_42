#include "../include/minishell.h"

int		ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
}

int		ft_search(char c, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return(1);
		i++;
	}
	return(0);
}

int		handle_quotes(char const *str, int i, t_data *data)
{
	if (str[i] == '\"')
	{
		i++;
		if (str[i] == '\0')
		{
			data->error->errno = QUOTE;
			data->error->value = ft_strdup("Quotes error (unclosed)");
			return(-1);
		}
		while (str[i] && str[i] != '\"')
		{
			if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
				i += 2;
			else
				i++;
			if (str[i] == '\0')
			{
				data->error->errno = QUOTE;
				data->error->value = ft_strdup("Quotes error (unclosed)");
				return(-1);
			}
		}
	}
	else
	{
		i++;
		if (str[i] == '\0')
		{
			data->error->errno = QUOTE;
			data->error->value = ft_strdup("Quotes error (unclosed)");
			return(-1);
		}
		while (str[i] && str[i] != '\'')
		{
			i++;
			if (str[i] == '\0')
			{
				data->error->errno = QUOTE;
				data->error->value = ft_strdup("Quotes error (unclosed)");
				return(-1);
			}
		}
	}
	i++;
	return (i);
}

int		quotes_length(char const *str, int i)
{
	int		length;

	length = 0;
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
		{
			if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
			{
				length += 2;
				i += 2;
			}
			else
			{
				length++;
				i++;
			}
		}
	}
	else
	{
		i++;
		while (str[i] && str[i] != '\'')
		{
			length++;
			i++;
		}
	}
	printf("LENGTH = %d\n",length);
	return (length + 1);
}

int		count_tokens(char const *str, t_data *data)
{
	int	i;
	int	nb_tokens;

	i = 0;
	nb_tokens = 0;
	while (str[i])
	{
		if (ft_isblank(str[i]))
		{
			while (str[i] && ft_isblank(str[i]))
				i++;
		}
		if (ft_search(str[i],";|<>"))
		{
			while (ft_search(str[i],";|<>"))
				i++;
			nb_tokens++;
		}
		if (str[i] == '\\')
		{
			i+= 2;
			nb_tokens++;
		}
		else if (str[i] && !(ft_isblank(str[i])) && !(ft_search(str[i],";|<>\'\"")))
		{
			while (str[i] && (!(ft_isblank(str[i]))	&& !(ft_search(str[i],";|<>\'\""))))
				i++;
			nb_tokens++;
		}
		else if (ft_search(str[i],"\"\'"))
		{
			i = handle_quotes(str, i, data);
			if (i == -1)
				return(-1);
			nb_tokens++;
		}
		else
		{
			while (str[i] && (ft_isblank(str[i])))
				i++;
		}
	}
	return (nb_tokens);
}

void	fill_tokens(char const *str, int nb_tokens, t_data *data)
{
	int		i;
	int		j;
	int		length;
	char	**tokens;

	i = 0;
	j = 0;
	if (!(data->tokens = malloc(sizeof(char *) * nb_tokens + 1)))
		return ;
	while (str[i])
	{
		if (ft_isblank(str[i]))
		{
			while (str[i] && ft_isblank(str[i]))
				i++;
		}
		if (ft_search(str[i],";|<>"))
		{
			length = 0;
			while (ft_search(str[i + length],";|<>"))
				length++;
			data->tokens[j] = ft_substr(str, i, length);
			i += length;
			j++;
		}
		if (str[i] == '\\')
		{
			data->tokens[j] = ft_substr(str, i, 2);
			i+= 2;
			j++;
		}
		else if (str[i] && !(ft_isblank(str[i])) && !(ft_search(str[i],";|<>\'\"")))
		{
			length = 0;
			while (str[i + length] && (!(ft_isblank(str[i + length])) && !(ft_search(str[i + length],";|<>\'\""))))
				length++;
			data->tokens[j] = ft_substr(str, i, length);
			j++;
			i += length;
		}
		else if (ft_search(str[i],"\"\'"))
		{
			length = quotes_length(str, i);
			i++;
			data->tokens[j] = ft_substr(str, i, length);
			j++;
			i += length + 1;
		}
		else
		{
			while (str[i] && (ft_isblank(str[i])))
				i++;
		}
	}
	data->tokens[j] = NULL;
}

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
		else if (ft_search(cmd[i],"\"\'"))
			i = skip_quotes(cmd,i);
		else if (cmd[i] == ';')
		{
			nb_cmd++;
			i++;
		}
		else
			i++;
	}
	return(nb_cmd);
}

int		find_start(char *cmd, int i)
{
	while (cmd[i] == ';')
		i++;
	while(cmd && ft_isblank(cmd[i]))
		i++;
	return (i);
}

int		find_end(char *cmd, int i)
{
	int		j;

	j = 0;
	if (cmd[i] == ';' || cmd[i] == '\0' )
		j++;
	while(cmd && ft_isblank(cmd[i - j]))
		j++;
	return ((i - j) + 1);
}

char	**split_command(char *cmd, int nb_cmd)
{
	int i;
	int j;
	int start;
	int end;
	char **cmds;

	if(!(cmds = malloc(sizeof(char *) * nb_cmd + 1)))
		return(NULL);
	i = 0;
	j = 0;
	start = find_start(cmd, i);
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i],"\"\'"))
			i = skip_quotes(cmd,i);
		else if (cmd[i] == ';')
		{
			end = find_end(cmd, i);
			cmds[j] = ft_substr(cmd, start, end - start);
			j++;
			start = find_start(cmd, i);
			i++;
		}
		else
			i++;
	}
	end = find_end(cmd, i);
	cmds[j] = ft_substr(cmd, start, end - start);
	j++;
	cmds[j] = NULL;
	return(cmds);
}

int		count_tokens(char *cmd)
{
	// count sep | < > >>
	int	i;
	int nb_tokens;

	i = 0;

	i = 0;
	nb_tokens = 1;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i],"\"\'"))
			i = skip_quotes(cmd,i);
		else if (ft_search(cmd[i], "|<>"))
		{
			nb_tokens++;
			if (!ft_strncmp(&cmd[i], ">>", 2))
				i += 2;
			else
				i++;
		}
		else
			i++;
	}
	return(nb_tokens);

}

char	**fill_tokens(char *cmd)
{
	// split sep | < > >>
	int	i;

	i = 0;
}

char		***split_tokens(char **cmds, int nb_cmds)
{
	int		i;
	int		nb_tokens;
	char	***tokens;

	i = 0;
	if (!(tokens = malloc(sizeof(char **) * nb_cmds)))
		return (NULL);
	while (cmds && cmds[i])
	{
		nb_tokens = count_tokens(cmds[i]);
		// if (!(tokens[i] = malloc(sizeof(char *) * nb_tokens)))
		// 	return (NULL);
		// tokens[i] = fill_tokens(cmds[i]);
		printf("nb_tokens = %d\n",nb_tokens);
		i++;
	}
	return(NULL);
}

char		**ft_lexer(t_data *data)
{
	printf("IN LEXER : %s\n", data->command);

	int		nb_cmds;
	char	**cmds;
	char	***tokens;

	nb_cmds = count_command(data->command);
	// printf("NB_CMD = %d\n", nb_cmd);
	cmds = split_command(data->command, nb_cmds);
	tokens = split_tokens(cmds, nb_cmds);
	// if (nb_cmd == -1)
	// 	return(NULL);
	// fill_tokens(data->command, nb_tokens, data);
	for (int i = 0; cmds[i]; i++)
		printf("CMDS[%d] = [%s]\n", i, cmds[i]);
	return (NULL);
}
