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

# define MAX_PATH_LENGTH 4096

# define TRUE 1
# define FALSE 0

int				EXIT_CODE;

char			*my_prompt;
pid_t			g_signal_receiver_pid = 0;


typedef int		t_bool;


typedef enum	e_type
{
	SEMI_COLON,
	AND,
	PIPE,
	REDIR_STDOUT,
	APP_STDOUT,
	REDIR_STDIN,
	COMMAND,
	FILE_R,
	ENV_VAR,
	DEFAULT
}				t_type;

typedef struct		s_struct
{
	t_type		type; //		&&			|
	char 		*command; //	NULL		NULL
	char		**options; //	NULL		NULL
	void		(*pf)(int, int); // pipe_create / redirection etc...
	void		*left; //		|			ls -l
	void		*right; //		ls			sort
}					t_struct;

typedef enum	e_redir_type
{
	NONE,
	REDIRECT_STDOUT,
	APPEND_STDOUT,
	REDIRECT_STDIN,
}				t_redir_type;

typedef	struct	s_redirection
{
	char			*str;
	t_redir_type	type;
	int				saved_stdout;
}				t_redirection;

int				ft_env(char **env);
void			ft_pwd(void);
void			ft_echo(char **env, char *command);
void			ft_cd(char *path);
void			ft_export(char ***env, char **splitted);
void			ft_unset(char ***env, char **splitted);

int				ft_indexof(char *str, char c);
char			**ft_lexer(char const *commands);

char			**get_env(char **env);
char 			*get_env_var(char **env, char *name);
t_bool			set_env_var(char **env, char *name, char *variable);

int				tab_str_len(char **tab);
void			free_tab_str(char **tab);

t_redirection	**set_redirections(char *command);
void			reset_redirections(t_redirection **redirections);

int 			*init_pipes(char **tokens);
void			pipe_io(int *pipes, int index);
void			close_pipes(int *pipes);
void			ast_exec(void);
int				ft_parser(char **commands);

#endif
