/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:06:03 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:06:05 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data		*init_data(char **env)
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	data->my_env = get_env(env);
	if (!(data->error = malloc(sizeof(t_error))))
		return (NULL);
	data->error->value = NULL;
	data->error->errtype = NOERROR;
	return (data);
}

t_command	*ft_init_command(void)
{
	t_command	*ptr;

	if (!(ptr = (t_command *)malloc(sizeof(t_command))))
		return (NULL);
	ptr->cmd = NULL;
	ptr->opt = NULL;
	ptr->opt_tab = NULL;
	ptr->redir = NULL;
	ptr->last_stdin = NULL;
	ptr->last_stdout = NULL;
	ptr->pipe = NULL;
	ptr->p_handled = FALSE;
	ptr->next = NULL;
	return (ptr);
}
