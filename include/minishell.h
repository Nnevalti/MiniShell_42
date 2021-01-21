/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:34:29 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/15 16:56:30 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# define 			MAX_PATH_LENGTH 4096

# define 			TRUE 1
# define 			FALSE 0

int					EXIT_CODE;

typedef int			t_bool;


typedef enum		e_type
{
	SEMI_COLON,
	PIPE,
	REDIR,
	COMMAND,
	DEFAULT
}					t_type;

typedef enum		e_redir_type
{
	NONE,
	REDIRECT_STDOUT,
	APPEND_STDOUT,
	REDIRECT_STDIN
}					t_redir_type;

typedef enum		e_errno
{
	NOERROR,
	QUOTE,
	PARSER,
	MALLOC

}					t_errno;

typedef struct		s_tree
{
	t_type			type; //		&&			|
	char 			*command; //	NULL		NULL
	char			**options; //	NULL		NULL
	t_redir_type	redir_type;
	char			*file;
	void			*left; //		|			ls -l
	void			*right; //		ls			sort
}					t_tree;

typedef	struct		s_redirection
{
	char			*str;
	t_redir_type	type;
	int				saved_stdout;
}					t_redirection;

typedef struct		s_error
{
	t_errno			errno;
	char			*value;
}					t_error;

typedef struct		s_data
{
	char			**my_env;
	char			*prompt;
	char			*command;
	char			*new_command;
	char			**tokens;
	t_tree			*parser;
	t_error			*error;
}					t_data;

t_data      		*init_data(char **env);

int					ft_env(char **env);
void				ft_pwd(void);
void				ft_echo(char **env, char *command);
void				ft_cd(char *path);
void				ft_export(char ***env, char **splitted);
void				ft_unset(char ***env, char **splitted);

int					ft_indexof(char *str, char c);
char				**ft_lexer(t_data *data);
void				handle_env(t_data *data);
char				**get_env(char **env);
char 				*get_env_var(char **env, char *name);
t_bool				set_env_var(char **env, char *name, char *variable);

int					tab_str_len(char **tab);
void				free_tab_str(char **tab);

t_redirection		**set_redirections(char *command);
void				reset_redirections(t_redirection **redirections);

int 				*init_pipes(char **tokens);
void				pipe_io(int *pipes, int index);
void				close_pipes(int *pipes);
void				ast_exec(t_tree *entry);
void				free_ast(t_tree *entry);
t_tree				*ft_parser(char **commands);

#endif
