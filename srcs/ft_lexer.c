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
	return (length);
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

char		**ft_lexer(t_data *data)
{
	printf("IN LEXER : %s\n", data->new_command);

	int		nb_tokens;

	nb_tokens = count_tokens(data->new_command, data);
	printf("NB_TOKENS = %d\n", nb_tokens);
	if (nb_tokens == -1)
		return(NULL);
	fill_tokens(data->new_command, nb_tokens, data);
	for (int i = 0; data->tokens[i]; i++)
		printf("TOKENS[%d] = [%s]\n", i, data->tokens[i]);
	return (data->tokens);
}
