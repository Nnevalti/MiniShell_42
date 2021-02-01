/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:52:27 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 18:52:31 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			skip_env(char const *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\\' && str[i + 1])
		i += 2;
	return (i);
}

int			ft_norme_again(char const *str, int *i, int len)
{
	(*i)++;
	while (ft_isalnum(str[(*i)]) || str[(*i)] == '_')
	{
		len++;
		(*i)++;
	}
	return (len);
}

char		*fill_env_array_utils(char const *str, char **env, int *env_len,
					int *i)
{
	int		len;
	char	*env_name;
	char	*env_array;

	len = 0;
	if (str[(*i)] == '$' && (ft_isalnum(str[(*i) + 1])
		|| ft_search(str[(*i) + 1], "_\'\"")))
	{
		len = ft_norme_again(str, i, len);
		env_name = ft_substr(&str[(*i) - len], 0, len);
		if (get_env_var(env, env_name) == NULL)
			env_array = ft_strdup("");
		else
			env_array = ft_strdup(get_env_var(env, env_name));
		free(env_name);
		*env_len += len + 1;
	}
	else if (str[(*i)] == '$' && str[(*i) + 1] == '?')
	{
		env_array = ft_itoa(errno);
		*env_len += 2;
	}
	return (env_array);
}

char		*fill_env_array(char const *str, char **env, int *env_len, int *i)
{
	char	*env_array;

	env_array = NULL;
	if (str[(*i)] == '\'' || (str[(*i)] == '\\' && str[(*i) + 1]))
		(*i) = skip_env(str, (*i));
	else if (str[(*i)] == '$')
		env_array = fill_env_array_utils(str, env, env_len, i);
	else if (str[(*i)])
		(*i)++;
	return (env_array);
}
