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
			if (str[i] == c && str[i + 1] == c)
			{
				printf("error parsing");
				return(-1);
			}
			if (str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
					i++;
			}
			if (str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
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
			while (str[i] && str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i])
			i++;
	}
	return (i);
}

char		**ft_split_command_line(char const *str)
{
	int		nb_strings;
	int		i;
	char	**result;
	int		length;

	nb_strings = ft_nb_tokens(str, ';');
	if (!(result = (char **)malloc((nb_strings + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < nb_strings)
	{
		length = fill_result(str, ';');
		result[i] = ft_substr(str, 0, length);
		str += length + 1;
		i++;
	}
	result[nb_strings] = NULL;
	return (result);
}
