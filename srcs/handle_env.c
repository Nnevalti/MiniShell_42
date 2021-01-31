#include "../include/minishell.h"

char		**get_env_array(char const *str, char **env, int nb_var, int *env_len)
{
	int		i;
	int		j;
	int		len;
	char	**env_array;
	char	*env_name;

	i = 0;
	j = 0;
	if (!(env_array = malloc(sizeof(char *) * (nb_var + 1))))
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
		if (str[i] == '\\' && str[i + 1])
			i += 2;
		if (str[i] == '$' && (ft_isalnum(str[i + 1])
			|| ft_search(str[i+1],"_\'\"")))
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
			*env_len += len + 1;
		}
		if (str[i] == '$' && str[i + 1] == '?')
		{
			env_array[j] = ft_itoa(errno);
			*env_len += 2;
			j++;
		}
		if (str[i] && str[i] != '$')
			i++;
	}
	env_array[j] = NULL;
	return (env_array);
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
		if (str[i] == '\\' && str[i + 1])
			i += 2;
		if (str[i] == '$' && (ft_isalnum(str[i + 1])
			|| ft_search(str[i+1],"_\'\"")))
			nb_var++;
		if (str[i] == '$' && str[i + 1])
			nb_var++;
		if (str[i])
			i++;
	}
	return (nb_var);
}

char		*get_new_str(char const *str, char *new_str, char **env_array)
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
		if (str[i] == '\\' && str[i + 1])
		{
			new_str[j] = str[i];
			new_str[j + 1] = str[i + 1];
			i += 2;
			j += 2;
		}
		if (str[i] == '$' && (ft_isalnum(str[i + 1])
			|| ft_search(str[i+1],"_\'\"")))
		{
			i++;
			while (ft_isalnum(str[i]) || ft_search(str[i+1],"_\'\""))
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
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
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

char		*handle_cmd_env(char *str, t_data *data)
{
	int		i;
	char	**env_array;
	int		env_len;
	int		len;
	char	*new_str;

	i = 0;
	env_len = 0;
	len = 0;
	env_array = get_env_array(str, data->my_env,
				get_nb_var(str), &env_len);
	while (env_array[i])
	{
		len += ft_strlen(env_array[i]);
		i++;
	}
	if (!(new_str = malloc(sizeof(char *) * (ft_strlen(str)
		- env_len + len + 1))))
		return (NULL);
	new_str = get_new_str(str, new_str, env_array);
	return (new_str);
}

void		handle_env(t_command *current, t_data *data)
{
	char	*tmp;
	t_redir	*redir_tmp;

	tmp = handle_cmd_env(current->cmd, data);
	free(current->cmd);
	current->cmd = tmp;
	if (current->opt)
	{
		tmp = handle_cmd_env(current->opt, data);
		free(current->opt);
		current->opt = tmp;
	}
	redir_tmp = current->redir;
	while (redir_tmp)
	{
		tmp = handle_cmd_env(redir_tmp->str, data);
		free(redir_tmp->str);
		redir_tmp->str = tmp;
		redir_tmp = redir_tmp->next;
	}
	return ;
}
