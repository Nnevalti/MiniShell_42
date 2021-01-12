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

int			fill_result(const char *str, char c)
{
	int		i;
	char	*result;

	i = 0;
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
		if (str[i])
			i++;
	}
	return (i);
}

char		**ft_lexer(char const *str)
{
	int		nb_tokens;
	int		i;
	char	**result;
	int		length;

	nb_tokens = ft_nb_tokens(str, ' ');
	printf("nb tokens : %d\n", nb_tokens);
	if (!(result = (char **)malloc((nb_tokens + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < nb_tokens)
	{
		length = fill_result(str, ';');
		result[i] = ft_substr(str, 0, length);
		str += length + 1;
		i++;
	}
	result[nb_tokens] = NULL;
	return (result);
}
