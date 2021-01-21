#include "../include/minishell.h"

char		**get_env_array(char const *str, char **env, int nb_var, int *total_len)
{
	int		i;
	int		j;
	int		len;
	char	**env_array;
	char	*env_name;

	i = 0;
	j = 0;
	if (!(env_array = malloc(sizeof(char *) * nb_var + 1)))
	{
		// data->error->errno = MALLOC;
		return (NULL);
	}
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
		if (str[i] == '$' && str[i + 1] == '?')
		{
			env_array[j] = ft_strdup(" $? ");
			*total_len += 4;
			j++;
			i += 2;
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
		else if (str[i] == '$' && str[i+1	] == '?')
		{
			l = 0;
			while (env_array[k][l])
			{
				new_str[j] = env_array[k][l];
				j++;
				l++;
			}
			k++;
			i += 2;
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
		if (str[i] == '$' && str[i + 1] == '?')
			nb_var++;
		if (str[i])
			i++;
	}
	return (nb_var);
}

void		handle_env(t_data *data)
{
	int		i;
	char	**env_array;
	int		env_len;
	int		len;

	i = 0;
	env_len = 0;
	len = 0;
	env_array = get_env_array(data->command, data->my_env,
				get_nb_var(data->command), &env_len);
	while (env_array[i])
	{
		len += ft_strlen(env_array[i]);
		i++;
	}
	if (!(data->new_command = malloc(sizeof(char *) * ft_strlen(data->command)
		- env_len + len + 1)))
	{
		data->error->errno = MALLOC;
		return ;
	}
	data->new_command = get_new_str(data->command, data->new_command, env_array);
	return ;
}
