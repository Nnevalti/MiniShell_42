/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:47:42 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 18:47:43 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		skip_newstr(char const *str, char *new_str, int *i, int *j)
{
	if (str[(*i)] == '\'')
	{
		new_str[(*j)] = str[(*i)];
		(*i)++;
		(*j)++;
		while (str[(*i)] && str[(*i)] != '\'')
		{
			new_str[(*j)] = str[(*i)];
			(*i)++;
			(*j)++;
		}
	}
	if (str[(*i)] == '\\' && str[(*i) + 1])
	{
		new_str[(*j)] = str[(*i)];
		new_str[(*j) + 1] = str[(*i) + 1];
		(*i) += 2;
		(*j) += 2;
	}
	return ;
}

int			skip_env_name(char const *str, int i)
{
	i++;
	while (ft_isalnum(str[i]) || ft_search(str[i + 1], "_"))
		i++;
	return (i);
}

void		copy_env_value(char *new_str, char **env_array, int *k, int *j)
{
	int	l;

	l = 0;
	while (env_array[(*k)][l])
	{
		new_str[(*j)] = env_array[(*k)][l];
		(*j)++;
		l++;
	}
	(*k)++;
	return ;
}

int			is_env_name(char const *str, int i)
{
	return (ft_isalnum(str[i + 1]) || ft_search(str[i + 1], "_\'\""));
}

void		init_normed_int(int *i, int *j, int *k)
{
	(*i) = 0;
	(*j) = 0;
	(*k) = 0;
}
