#include "minishell.h"

static int	ft_nb_strings(char const *str)
{
	int		nb_strings;
	int		i;
	int		j;

	i = 0;
	nb_strings = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == ';')
		{
			if (str[i] == ';' && str[i + 1] == ';')
			{
				ft_printf("error parsing");
				return(-1);
			}
			i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
			{
				i++;
			}
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				i++;
			}
		}
		if (str[i] != '\0')
		{
			nb_strings++;
		}
		while (str[i] && str[i] != ' ' && str[i] != ';')
			i++;
	}
	return (nb_strings);
}

char		*fill_result(const char *str)
{
	int		i;
	int		length;
	char 	*result;

	length = 0;
	while (*str == ' ' || *str == ';')
		str++;
	i = 0;
	if (str[i] == '"')
	{
		str++;
		while (str[i] != '"')
		{
			length++;
			i++;
		}
	}
	else if (str[i] == '\'')
	{
		str++;
		while (str[i] != '\'')
		{
			length++;
			i++;
		}
	}
	else
	{
		while (str[i] && str[i] != ' ' && str[i] != ';')
		{
			length++;
			i++;
		}
	}
	if (!(result = (char *)malloc((length + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	ft_printf("fill: %s\n", result);
	return(result);
}

char		**ft_split_command_line(char const *str)
{
	int		nb_strings;
	int		i;
	char	**result;

	nb_strings = ft_nb_strings(str);
	ft_printf("%d\n", nb_strings);
	if (!(result = (char **)malloc((nb_strings + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (*str == ' ' || *str == ';' )
		str++;
	while (i < nb_strings)
	{
		result[i] = fill_result(str);
		ft_printf("result : %s\n", result[i]);
		i++;
		while(*str && *str != ' ' && *str != ';')
			str++;
	}
	result[nb_strings] = NULL;
	return (result);
}
