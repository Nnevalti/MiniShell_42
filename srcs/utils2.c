/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:06:39 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:06:42 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**prepend_str(char *str, char **array_str)
{
	int		i;
	int		j;
	char	**new_array;

	i = tab_str_len(array_str);
	if (!(new_array = malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	new_array[0] = ft_strdup(str);
	i = 1;
	j = 0;
	while (array_str[j])
	{
		new_array[i] = ft_strdup(array_str[j]);
		i++;
		j++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	ft_puterror(char *str1, char *str2, char *str3)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	return ;
}

void	ft_error_min_max(t_data *data, t_command *cmd, unsigned long long res)
{
	if (cmd->opt_tab[1][0] == '-')
	{
		if (((res * -1) - 1) > 9223372036854775807ULL)
		{
			errno = 2;
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(cmd->opt_tab[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
	}
	else
	{
		if (res > 9223372036854775807ULL)
		{
			errno = 2;
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(cmd->opt_tab[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
	}
}
