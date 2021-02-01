/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:34 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 15:04:35 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_env_array(char **env_array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_array[i])
	{
		j = 1;
		while (env_array[j + i])
		{
			if (ft_strcmp(env_array[j + i], env_array[i]) < 0)
			{
				tmp = env_array[i];
				env_array[i] = env_array[i + j];
				env_array[i + j] = tmp;
			}
			j++;
		}
		i++;
	}
	ft_env(NULL, env_array);
}

char	**create_sort_env(char **env)
{
	int		i;
	int		j;
	char	**sort_env;

	i = 0;
	j = 0;
	while (env[i + j])
	{
		if (env[i + j][0] == '_')
			j++;
		else
			i++;
	}
	if (!(sort_env = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	return (sort_env);
}

void	sort_export(char **env)
{
	char	**sort_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sort_env = create_sort_env(env);
	while (env[i + j])
	{
		if (env[i + j][0] == '_')
			j++;
		else
		{
			sort_env[i] = ft_strjoin("declare -x ", env[i + j]);
			i++;
		}
	}
	sort_env[i] = NULL;
	sort_env_array(sort_env);
	free_tab_str(sort_env);
	return ;
}

int		ft_export_utils(t_data *data, t_command *ptr, int i)
{
	int		j;
	int		nb_vars;
	char	**new_env;

	nb_vars = 0;
	while (data->my_env[nb_vars])
		nb_vars++;
	if (!(new_env = malloc((nb_vars + 2) * sizeof(char *))))
		return (-1);
	j = 0;
	while (j < nb_vars)
	{
		new_env[j] = ft_strdup(data->my_env[j]);
		j++;
	}
	new_env[j] = ft_strdup(ptr->opt_tab[i]);
	new_env[j + 1] = NULL;
	free_tab_str(data->my_env);
	data->my_env = new_env;
	return (0);
}

void	ft_export(t_data *data, t_command *ptr)
{
	int		i;
	char	*name;

	i = 0;
	if (tab_str_len(ptr->opt_tab) == 1)
		sort_export(data->my_env);
	while (ptr->opt_tab[i])
	{
		if (ft_indexof(ptr->opt_tab[i], '=') < 0)
		{
			i++;
			continue;
		}
		name = ft_substr(ptr->opt_tab[i], 0, ft_indexof(ptr->opt_tab[i], '='));
		if (!set_env_var(data->my_env, name, ptr->opt_tab[i]))
			if (ft_export_utils(data, ptr, i) == -1)
				return ;
		free(name);
		i++;
	}
	return ;
}
