/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:06:12 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:06:13 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		skip_opt(int i, char *opt)
{
	if (opt[i] == '\"')
	{
		i++;
		while (opt[i] != '\"')
		{
			if (opt[i] == '\\')
				i += 2;
			else
				i++;
		}
		i++;
	}
	else if (opt[i] == '\'')
	{
		i++;
		while (opt[i] != '\'')
			i++;
		i++;
	}
	else if (opt[i] == '\\')
		i += 2;
	return (i);
}

int		skip_opt_blank(char *opt, int i)
{
	while (ft_isblank(opt[i]))
		i++;
	return (i);
}

int		get_nb_opt(char *opt)
{
	int i;
	int nb_opt;

	i = 0;
	nb_opt = 1;
	while (opt[i])
	{
		if (opt[i] == '\"' || opt[i] == '\'' || opt[i] == '\\')
			i = skip_opt(i, opt);
		else if (ft_isblank(opt[i]))
		{
			i++;
			while (ft_isblank(opt[i]))
				i++;
			nb_opt++;
		}
		else
			i++;
	}
	return (nb_opt);
}

void	get_opt_tab(t_command *current, char *opt)
{
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	i = skip_opt_blank(opt, i);
	start = i;
	while (opt[i])
	{
		if (opt[i] == '\"' || opt[i] == '\'' || opt[i] == '\\')
			i = skip_opt(i, opt);
		else if (ft_isblank(opt[i]))
		{
			current->opt_tab[j++] = ft_substr(opt, start, i - start);
			i++;
			i = skip_opt_blank(opt, i);
			start = i;
		}
		else
			i++;
	}
	current->opt_tab[j++] = ft_substr(opt, start, i - start);
	current->opt_tab[j] = NULL;
	return ;
}

void	create_opt_tab(t_command *current, t_data *data)
{
	int nb_opt;

	if (current->opt)
	{
		nb_opt = get_nb_opt(current->opt);
		if (!(current->opt_tab = malloc(sizeof(char *) * (nb_opt + 1))))
			return ;
		get_opt_tab(current, current->opt);
	}
	return ;
}
