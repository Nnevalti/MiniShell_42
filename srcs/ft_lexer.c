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

static int	ft_nb_tokens(char const *str)
{
	int		nb_tokens;
	int		i;

	i = 0;
	nb_tokens = 0;
	while (str[i])
	{
		while (str[i] && (!(ft_isblank(str[i])) && str[i] != ';'))
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
	while (str[i] && (str[i] != c || (str[i - 1] == '\\' && str[i - 2] != '\\')))
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

int			get_nb_var(char const *str)
{
	int		i;
	int		nb_var;

	i = 0;
	nb_var = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			nb_var++;
		if (str[i])
			i++;
	}
	return (nb_var);
}

char		**get_env_array(char const *str, int nb_var, char **env, int *total_len)
{
	int		i;
	int		j;
	int		len;
	char	**env_array;
	char	*env_name;

	i = 0;
	j = 0;
	if (!(env_array = malloc(sizeof(char *) * nb_var + 1)))
		return (NULL);
	while (str[i] && j < nb_var)
	{
		len = 0;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			while (ft_isalnum(str[i]) || str[i] == '_')
			{
				len++;
				i++;
			}
			env_name = ft_substr(&str[i - len], 0, len);
			if (get_env_var(env, env_name) == NULL)
				env_array[j] = ft_strdup("");
			else
				env_array[j] = ft_strdup(get_env_var(env, env_name));
			free(env_name);
			j++;
			*total_len += len + 1;
		}
		if (str[i] && str[i] != '$')
			i++;
	}
	env_array[j] = NULL;
	return (env_array);
}

char	*get_new_str(char const *str, char *new_str, char **env_array)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			new_str[j] = str[i];
			i++;
			j++;
			while (str[i] && str[i] != '\'')
			{
				new_str[j] = str[i];
				i++;
				j++;
			}
		}
		if (str[i] == '$' && (ft_isalnum(str[i + 1])
			|| str[i + 1] == '_'))
		{
			i++;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			l = 0;
			while (env_array[k][l])
			{
				new_str[j] = env_array[k][l];
				j++;
				l++;
			}
			k++;
		}
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	free_tab_str(env_array);
	new_str[j] = '\0';
	return (new_str);
}
char		*handle_env(char **env, char const *str)
{
	int		i;
	int		nb_var;
	char	**env_array;
	char	*new_str;
	int		env_len;
	int		len;

	i = 0;
	nb_var = 0;
	env_len = 0;
	len = 0;
	nb_var = get_nb_var(str);
	env_array = get_env_array(str, nb_var, env, &env_len);
	while (env_array[i])
	{
		len += ft_strlen(env_array[i]);
		i++;
	}
	if (!(new_str = malloc(sizeof(char *) * ft_strlen(str) - env_len + len + 1)))
		return (NULL);
	new_str = get_new_str(str, new_str, env_array);
	return (new_str);
}

char		**ft_lexer(char const *str, char **env)
{
	int		nb_tokens;
	int		i;
	int		j;
	char	**result;
	int		length;
	char	*new_str;

	new_str = handle_env(env, str);
	nb_tokens = ft_nb_tokens(new_str); // count malloc
	if (!(result = (char **)malloc((nb_tokens + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < nb_tokens)
	{
		length = fill_result(&new_str[j], ' ');
		if (new_str[j] == '"')
			j++;
		result[i] = ft_substr(new_str, j, length);
		j += length + 1;
		if (new_str[j] == ' ')
			j++;
		i++;
	}
	printf("new_str %s\n",new_str);
	free(new_str);
	result[nb_tokens] = NULL;
	return (result);
}
