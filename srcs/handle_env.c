/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:05:05 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:05:06 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		**get_env_array(char const *str, char **env,
				int nb_var, int *env_len)
{
	int		i;
	int		j;
	char	**env_array;

	i = 0;
	j = 0;
	if (!(env_array = malloc(sizeof(char *) * (nb_var + 1))))
		return (NULL);
	while (str[i] && j < nb_var)
	{
		env_array[j] = fill_env_array(str, env, env_len, &i);
		if (env_array[j] != NULL)
			j++;
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
		if (str[i] == '\'' || (str[i] == '\\' && str[i + 1]))
			i = skip_env(str, i);
		else if (str[i] == '$' && (ft_isalnum(str[i + 1])
			|| ft_search(str[i + 1], "_\'\"?")))
		{
			nb_var++;
			i++;
		}
		else if (str[i])
			i++;
	}
	return (nb_var);
}

char		*get_new_str(char const *str, char *new_str, char **env_array)
{
	int		i;
	int		j;
	int		k;

	init_normed_int(&i, &j, &k);
	while (str[i])
	{
		if (str[i] == '\'' || (str[i] == '\\' && str[i + 1]))
			skip_newstr(str, new_str, &i, &j);
		if (str[i] == '$' && is_env_name(str, i))
		{
			i = skip_env_name(str, i);
			copy_env_value(new_str, env_array, &k, &j);
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
			copy_env_value(new_str, env_array, &k, &j);
		}
		else
			new_str[j++] = str[i++];
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
