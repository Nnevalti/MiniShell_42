#include "../include/minishell.h"

int		ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
}

int		pass_quotes(const char *str, int i)
{
	i++;
	while (str[i] && (str[i] != '"' || str[i - 1] == '\\'))
		i++;
	return (i);
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

static int	ft_nb_tokens(char const *str)
{
	int		nb_tokens;
	int		i;

	i = 0;
	nb_tokens = 0;
	while (str[i])
	{
		while (str[i] && (ft_strncmp(&str[i], ">>", 2)
		&& !(ft_search(str[i],";|<>")) && !(ft_isblank(str[i]))))
		{
			if (str[i] == '"')
			{
				i = pass_quotes(str, i);
			}
			if (str[i] == '\'')
			{
				while (str[i] && str[i] != '\'')
					i++;
			}
			i++;
		}
		if(ft_search(str[i],";|<>") || !(ft_strncmp(&str[i], ">>", 2)))
		{
			if(!(ft_strncmp(&str[i], ">>", 2)))
				i+=2;
			nb_tokens++;
		}
		if (str[i])
			i++;
		nb_tokens++;
	}
	return (nb_tokens);
}

int			string_count(const char *str, char c)
{
	int		i;
	int		j;
	int		length;

	i = 0;
	j = 0;
	length = 0;
	if (c == '"')
	{
		while (str[i] && (str[i] != c || (str[i - 1] == '\\' && str[i - 2] != '\\')))
		{
			i++;
			length++;
		}
	}
	else
	{
		while(str[i] && str[i] != c)
		{
			i++;
			length++;
		}
	}
	return(length);
}

int			fill_result(const char *str)
{
	int		i;
	int		length;
	char	*result;

	i = 0;
	length = 0;
	while (str[i] && (!(ft_search(str[i],";|<>"))
	&& ft_strncmp(&str[i], ">>", 2) && !(ft_isblank(str[i]))))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			length = string_count(&str[i + 1], str[i]);
			i += length + 1;
			return (length);
		}
		length++;
		i++;
	}
	return (length);
}

char		**ft_lexer(char const *str)
{
	int		nb_tokens;
	int		i;
	int		j;
	char	**result;
	int		length;

	nb_tokens = ft_nb_tokens(str); // count malloc
	printf("nb_tokens %d\n",nb_tokens);
	if (!(result = (char **)malloc((nb_tokens + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < nb_tokens)
	{
		length = fill_result(&str[j]);
		if (str[j] == '"')
			j++;
		result[i] = ft_substr(str, j, length);
		j += length + 1;
		if (str[j] == ' ')
			j++;
		i++;
	}
	printf("str %s\n",str);
	result[nb_tokens] = NULL;
	return (result);
}
