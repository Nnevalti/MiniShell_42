/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:13:00 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:13:03 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(void)
{
	char	buffer[MAX_PATH_LENGTH];

	getcwd(buffer, MAX_PATH_LENGTH);
	ft_putstr_fd("\e[1m\e[32m", 2);
	ft_putstr_fd(g_prompt, 2);
	ft_putstr_fd("@minishell:", 2);
	ft_putstr_fd("\e[94m", 2);
	ft_putstr_fd(buffer, 2);
	ft_putstr_fd("\e[39m$> \e[0m", 2);
}
