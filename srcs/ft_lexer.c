/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:04:23 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:04:24 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**split_command(char *cmd, int nb_cmd, char **cmds, int start)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	start = find_start(cmd, i, ";");
	while (cmd && cmd[i] && j < nb_cmd)
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i], "\"\'"))
			i = skip_quotes(cmd, i);
		else if (cmd[i] == ';')
		{
			cmds[j++] = ft_substr(cmd, start, find_end(cmd, i, ";") - start);
			start = find_start(cmd, i, ";");
			i++;
		}
		else
			i++;
	}
	if (j < nb_cmd)
		cmds[j++] = ft_substr(cmd, start, find_end(cmd, i, ";") - start);
	cmds[j] = '\0';
	return (cmds);
}

int		count_tokens(char *cmd)
{
	int	i;
	int nb_tokens;

	i = 0;
	nb_tokens = 1;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i], "\"\'"))
			i = skip_quotes(cmd, i);
		else if (ft_search(cmd[i], "|<>"))
		{
			nb_tokens++;
			if (!ft_strncmp(&cmd[i], ">>", 2))
				i += 2;
			else
				i++;
		}
		else
			i++;
	}
	return (nb_tokens);
}

char	**fill_tokens(char *cmd, int nb_tokens)
{
	int		i;
	int		j;
	int		start;
	char	**tokens;

	if (!(tokens = malloc(sizeof(char *) * (nb_tokens + 1))))
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (cmd && cmd[i])
	{
		tokens[j] = fill_tokens_utils(cmd, &start, &i);
		if (tokens[j] != NULL)
			j++;
	}
	tokens[j++] = ft_substr(cmd, start, find_end(cmd, i, "|<>") - start);
	tokens[j] = NULL;
	return (tokens);
}

char	***split_tokens(char **cmds, int nb_cmds)
{
	int		i;
	int		nb_tokens;
	char	***tokens;

	i = 0;
	if (!(tokens = malloc(sizeof(char **) * (nb_cmds + 1))))
		return (NULL);
	while (cmds && cmds[i] && i < nb_cmds)
	{
		nb_tokens = count_tokens(cmds[i]);
		tokens[i] = fill_tokens(cmds[i], nb_tokens);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

char	***ft_lexer(t_data *data)
{
	char	**cmds;
	char	***tokens;
	int		start;

	data->nb_cmds = count_command(data->command);
	if (!(cmds = malloc(sizeof(char *) * (data->nb_cmds + 1))))
		return (NULL);
	cmds = split_command(data->command, data->nb_cmds, cmds, start);
	tokens = split_tokens(cmds, data->nb_cmds);
	free_tab_str(cmds);
	return (tokens);
}
