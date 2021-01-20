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

int		handle_quotes(char const *str, int i)
{
	if (str[i] == '\"')
	{
		i++;
		if (str[i] == '\0')
		{
			printf("quotes pb\n");
			exit(0);
		}
		while (str[i] && str[i] != '\"')
		{
			if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
				i += 2;
			else
				i++;
			if (str[i] == '\0')
			{
				printf("quotes pb\n");
				exit(0);
			}
		}
	}
	else
	{
		i++;
		if (str[i] == '\0')
		{
			printf("quotes pb\n");
			exit(0);
		}
		while (str[i] && str[i] != '\'')
		{
			i++;
			if (str[i] == '\0')
			{
				printf("quotes pb\n");
				exit(0);
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

int		count_tokens(char const *str)
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
			i = handle_quotes(str, i);
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

char		**fill_tokens(char const *str, int nb_tokens)
{
	int		i;
	int		j;
	int		length;
	char	**tokens;

	i = 0;
	j = 0;
	if (!(tokens = malloc(sizeof(char *) * nb_tokens + 1)))
		return (NULL);
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
			tokens[j] = ft_substr(str, i, length);
			i += length;
			j++;
		}
		if (str[i] == '\\')
		{
			tokens[j] = ft_substr(str, i, 2);
			i+= 2;
			j++;
		}
		else if (str[i] && !(ft_isblank(str[i])) && !(ft_search(str[i],";|<>\'\"")))
		{
			length = 0;
			while (str[i + length] && (!(ft_isblank(str[i + length])) && !(ft_search(str[i + length],";|<>\'\""))))
				length++;
			tokens[j] = ft_substr(str, i, length);
			j++;
			i += length;
		}
		else if (ft_search(str[i],"\"\'"))
		{
			length = quotes_length(str, i);
			i++;
			tokens[j] = ft_substr(str, i, length);
			j++;
			i += length + 1;
		}
		else
		{
			while (str[i] && (ft_isblank(str[i])))
				i++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}

char		**ft_lexer(char const *str)
{
	printf("IN LEXER : %s\n", str);

	int		nb_tokens;
	char	**tokens;

	nb_tokens = count_tokens(str);
	printf("NB_TOKENS = %d\n", nb_tokens);
	tokens = fill_tokens(str, nb_tokens);
	for (int i = 0; tokens[i]; i++)
		printf("TOKENS[%d] = [%s]\n", i, tokens[i]);
	return (tokens);
}
