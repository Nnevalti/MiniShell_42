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

// typedef enum		e_type
// {
// 	PIPE,
// 	REDIR,
// 	COMMAND,
// 	DEFAULT
// }					t_type;

// typedef struct		s_tree
// {
// 	t_type			type; //		&&			|
// 	char 			*command; //	NULL		NULL
// 	char			*options; //	NULL		NULL
// 	t_redir_type	redir_type;
// 	char			*file;
// 	void			*left; //		|			ls -l
// 	void			*right; //		ls			sort
// }					t_tree;
typedef enum		e_redir_type
{
	NONE,
	REDIRECT_STDOUT,
	APPEND_STDOUT,
	REDIRECT_STDIN
}					t_redir_type;

typedef	struct		s_redir
{
	char			*str; // File name
	t_redir_type	type; // redirection type [>, <, >>]
	int				saved_fd; // saved fd from the open(file)
	void			*next; // next redirection to do if = NULL -> end
}					t_redir;

typedef struct		s_pipe
{
	// IN ? TRUE / FALSE
	// OUT ? TRUE / FALSE
	// int STDIN_PIPE[2];
	// int STDOUT_PIPE[2];
}					t_pipe;

typedef struct		s_command
{
	char 			*cmd; // echo
	char 			*opt; //-n test pute etc...
	t_redir			*redir; // pointeur vers la structure redir
	t_pipe			*pipe;	// IDK yet but something
	void			*next; // Next command to process if = NULL -> end
	void			*previous;

}					t_command;

typedef enum		e_errno
{
	NOERROR,
	QUOTE,
	PARSER,
	MALLOC

}					t_errno;

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
	char			***tokens;
	int				nb_cmds;
	t_command		*parser;
	t_error			*error;
}					t_data;

t_data      		*init_data(char **env);

int					ft_env(char **env);
void				ft_pwd(void);
void				ft_echo(t_command *ptr);
void				ft_cd(t_data *data, t_command *ptr);
void				ft_export(t_data *data, t_command *ptr);
void				ft_unset(t_data *data, t_command *ptr);

int					ft_indexof(char *str, char c);
char				***ft_lexer(t_data *data);
void				handle_env(t_data *data);
char				**get_env(char **env);
char 				*get_env_var(char **env, char *name);
t_bool				set_env_var(char **env, char *name, char *variable);

int					tab_str_len(char **tab);
void				free_tab_str(char **tab);
void				free_tokens(char ***tokens);


t_redir				**set_redirections(char *command);
void				reset_redirections(t_redir **redirections);

int 				*init_pipes(char **tokens);
void				pipe_io(int *pipes, int index);
void				close_pipes(int *pipes);
void				ast_exec(t_data *data);
void				free_ast(t_command *entry);
t_command			*ft_parser(t_data *data);

int					ft_isblank(char c);
int					ft_search(char c, char *str);

void 				handle_error(t_data *data);
int					check_error(t_data *data, char ***tokens);

#endif
