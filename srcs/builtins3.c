/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:30:00 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 15:30:03 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_env(t_command *cmd, char **env)
{
	int		i;

	i = 0;
	if (cmd && cmd->opt_tab && (tab_str_len(cmd->opt_tab) > 1))
	{
		errno = 1;
		return (1);
	}
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}

int		ft_unsetnorme(t_data *data, int j, t_command *ptr, int i)
{
	return (ft_indexof(data->my_env[j], '=') < ft_strlen(ptr->opt_tab[i])
		? ft_strlen(ptr->opt_tab[i]) : ft_indexof(data->my_env[j], '='));
}

int		ft_unset_utils(t_data *data, t_command *ptr, int i, int nb_vars)
{
	int		j;
	int		k;
	char	**new_env;
	int		index;

	if (get_env_var(data->my_env, ptr->opt_tab[i]))
	{
		while (data->my_env[nb_vars])
			nb_vars++;
		if (!(new_env = malloc(nb_vars * sizeof(char *))))
			return (-1);
		j = 0;
		k = 0;
		while (j < nb_vars)
		{
			index = ft_unsetnorme(data, j, ptr, i);
			if (ft_strncmp(data->my_env[j], ptr->opt_tab[i], index))
				new_env[k++] = ft_strdup(data->my_env[j]);
			j++;
		}
		new_env[k] = NULL;
		free_tab_str(data->my_env);
		data->my_env = new_env;
	}
	return (0);
}

void	ft_unset(t_data *data, t_command *ptr)
{
	int		i;
	int		nb_vars;

	i = 0;
	while (ptr->opt_tab[i])
	{
		nb_vars = 0;
		if (ft_unset_utils(data, ptr, i, nb_vars) == -1)
			return ;
		i++;
	}
	return ;
}
