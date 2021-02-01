/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:04:38 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:04:39 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_set_redir(t_redir *redir, char *token, t_command *ptr,
							t_redir_type type)
{
	int		i;
	int		j;
	char	*tmp;

	i = ft_set_redir_utils(token, redir, type);
	if (token[i])
	{
		if (ptr->opt)
		{
			tmp = ft_strjoin(ptr->opt, " ");
			free(ptr->opt);
			ptr->opt = tmp;
			tmp = ft_strjoin(ptr->opt, &token[i]);
			free(ptr->opt);
			ptr->opt = tmp;
		}
		else
			ptr->opt = ft_strdup(&token[i]);
	}
	return ;
}

int			find_redir(char **tokens, t_command *ptr)
{
	int		i;
	t_redir *redir;

	ptr->redir = ft_init_redir();
	redir = ptr->redir;
	i = 0;
	while (tokens[i] && (tokens[i][0] == '<' || tokens[i][0] == '>'))
	{
		if (i > 0)
		{
			redir->next = ft_init_redir();
			redir = redir->next;
		}
		if (!(ft_strncmp(tokens[i], ">>", 2)))
			ft_set_redir(redir, &tokens[i][2], ptr, APPEND_STDOUT);
		else if (tokens[i][0] == '>')
			ft_set_redir(redir, &tokens[i][1], ptr, REDIRECT_STDOUT);
		else if (tokens[i][0] == '<')
			ft_set_redir(redir, &tokens[i][1], ptr, REDIRECT_STDIN);
		if (tokens[i])
			i++;
	}
	return (i - 1);
}

void		parse_commands(char **tokens, t_command *ptr)
{
	int			i;
	int			j;
	t_command	*current;

	current = ptr;
	i = 1;
	while (tokens[i])
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i += find_redir(&tokens[i], current);
		else if (tokens[i][0] == '|')
		{
			init_pipe_out(current);
			j = 1;
			while (ft_isblank(tokens[i][j]))
				j++;
			current->next = ft_create_struct(&tokens[i][j]);
			current = current->next;
			init_pipe_in(current);
		}
		if (tokens[i])
			i++;
	}
	return ;
}

t_command	**ft_parser(t_data *data)
{
	t_command	**entry;
	int			i;

	i = 0;
	if (!(entry = malloc(sizeof(t_command *) * (data->nb_cmds + 1))))
		return (NULL);
	while (data->tokens[i])
	{
		entry[i] = ft_create_struct(data->tokens[i][0]);
		if (multiple_commands(data->tokens[i]))
			parse_commands(data->tokens[i], entry[i]);
		i++;
	}
	entry[i] = NULL;
	return (entry);
}
