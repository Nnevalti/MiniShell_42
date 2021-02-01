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

t_redir		*ft_init_redir(void)
{
	t_redir	*redir;

	if (!(redir = (t_redir *)malloc(sizeof(t_redir))))
		return (NULL);
	redir->str = NULL;
	redir->type = NONE;
	redir->saved_fd = 0;
	redir->fd = 0;
	redir->next = NULL;
	return (redir);
}

t_pipe		*ft_init_pipe(void)
{
	t_pipe	*pipe;

	if (!(pipe = (t_pipe *)malloc(sizeof(t_pipe))))
		return (NULL);
	pipe->in = FALSE;
	pipe->out = FALSE;
	// ERROR PATCH :
	pipe->stdin[0] = 0;
	pipe->stdin[1] = 0;
	pipe->stdout[0] = 0;
	pipe->stdout[1] = 0;
	return (pipe);
}

t_command	*ft_create_struct(char *tokens)
{
	t_command	*ptr;
	int			i;

	i = 0;
	ptr = ft_init_command();
	while (tokens[i])
	{
		if (ft_isblank(tokens[i]))
		{
			ptr->cmd = ft_substr(tokens, 0, i);
			while (ft_isblank(tokens[i]))
				i++;
			if (tokens[i] == '\0')
				return (ptr);
			else
			{
				ptr->opt = ft_substr(tokens, i, ft_strlen(&tokens[i]));
				return (ptr);
			}
		}
		i++;
	}
	ptr->cmd = ft_strdup(tokens);
	return (ptr);
}

int			multiple_commands(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	if (i > 1)
		return (1);
	return (0);
}

void		ft_set_redir(t_redir *redir, char *token, t_command *ptr, t_redir_type type)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (token[i] && ft_isblank(token[i]))
		i++;
	j = 0;
	while (!(ft_isblank(token[i + j])) && token[i + j] != '\0')
		j++;
	redir->str = ft_substr(token, i, j);
	redir->type = type;
	i = i + j;
	while (token[i] && ft_isblank(token[i]))
		i++;
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

void		init_pipe_out(t_command *ptr)
{
	if (!(ptr->pipe))
		ptr->pipe = ft_init_pipe();
	ptr->pipe->out = TRUE;
}

void		init_pipe_in(t_command *ptr)
{
	if (!(ptr->pipe))
		ptr->pipe = ft_init_pipe();
	ptr->pipe->in = TRUE;
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
		return(NULL);
	while (data->tokens[i])
	{
		entry[i] = ft_create_struct(data->tokens[i][0]);
		if (multiple_commands(data->tokens[i]))
			parse_commands(data->tokens[i], entry[i]);
		// // FOR DEBUGGING
		// printf("IN PARSE COMMANDS\n");
		// t_command	*test;
		// t_redir 	*redir;
		// test = entry[i];
		// while (test)
		// {
		// 	printf("entry->cmd = [%s]\nentry->opt = [%s]\n",test->cmd, test->opt);
		// 	redir = test->redir;
		// 	while (redir)
		// 	{
		// 		printf("REDIR : type = %d / file = %s\n", redir->type, redir->str);
		// 		redir = redir->next;
		// 	}
		// 	if (test->pipe)
		// 		printf("PIPE : in = %d / out = %d\n", test->pipe->in, test->pipe->out);
		// 	test = test->next;
		// }
		// END DEBUGGING
		i++;
	}
	entry[i] = NULL;
	return (entry);
}
