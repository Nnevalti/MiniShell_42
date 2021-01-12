#include "minishell.h"

static int	ft_nb_tokens(char const *str, char c)
{
	int		nb_tokens;
	int		i;

	i = 0;
	nb_tokens = 0;
	while (str[i])
	{
		while (str[i] && str[i] != c)
		{
			if (str[i] == '"')
			{
				i++;
				while (str[i] && (str[i] != '"' || str[i - 1] == '\\'))
					i++;
			}
			if (str[i] == '\'')
			{
				i++;
				while (str[i] && (str[i] != '\'' || str[i - 1] == '\\'))
					i++;
			}
			i++;
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
	int		length;

	i = 0;
	length = 0;
	while (str[i] && (str[i] != c || str[i - 1] == '\\'))
	{
		i++;
		length++;
	}
	i++;
	return(length);
}

int			fill_result(const char *str, char c)
{
	int		i;
	int		length;
	char	*result;

	i = 0;
	length = 0;
	while (str[i] && str[i] != c)
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

	nb_tokens = ft_nb_tokens(str, ' ');
	// printf("nb tokens : %d\n", nb_tokens);
	if (!(result = (char **)malloc((nb_tokens + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < nb_tokens)
	{
		length = fill_result(&str[j], ' ');
		if (str[j] == '"')
			j++;
		result[i] = ft_substr(str, j, length);
		j += length + 1;
		i++;
	}
	result[nb_tokens] = NULL;
	return (result);
}
