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
# include <errno.h>

# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# define MAX_PATH_LENGTH 4096

pid_t	g_pid[2];
char	*g_prompt;

typedef enum			e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum		e_redir_type
{
	NONE,
	REDIRECT_STDOUT,
	APPEND_STDOUT,
	REDIRECT_STDIN
}					t_redir_type;

typedef	struct		s_redir
{
	char			*str;
	t_redir_type	type;
	int				saved_fd;
	int				fd;
	void			*next;
}					t_redir;

typedef struct		s_pipe
{
	t_bool			in;
	t_bool			out;
	int				stdin[2];
	int				stdout[2];
}					t_pipe;

typedef struct		s_command
{
	char			*cmd;
	char			*opt;
	char			**opt_tab;
	t_redir			*redir;
	t_redir			*last_stdin;
	t_redir			*last_stdout;
	t_pipe			*pipe;
	t_bool			p_handled;
	void			*next;
}					t_command;

typedef enum		e_errtype
{
	NOERROR,
	QUOTE,
	PARSER,
	SYNTAX,
	FD
}					t_errtype;

typedef struct		s_error
{
	t_errtype			errtype;
	char			*value;
}					t_error;

typedef struct		s_data
{
	char			**my_env;
	char			*command;
	char			***tokens;
	int				nb_cmds;
	t_command		**parser;
	t_error			*error;
}					t_data;

/*
**		INIT
*/
t_data				*init_data(char **env);
t_command			*ft_init_command(void);
t_redir				*ft_init_redir(void);
t_pipe				*ft_init_pipe(void);
void				init_pipe_out(t_command *ptr);
void				init_pipe_in(t_command *ptr);
/*
**		CORE
*/
void				prompt(void);
char				***ft_lexer(t_data *data);
t_command			**ft_parser(t_data *data);
void				ft_executor(t_data *data);
void				handle_env(t_command *current, t_data *data);
void				create_opt_tab(t_command *current, t_data *data);
void				handle_bsq(t_command *current, t_data *data);
void				exec_cmd(t_data *data, t_command *current);
void				handle_exit(t_data *data, t_command *cmd);
/*
**	SIGNAL
*/
void				kill_prg(int sig);
void 				signal_handler(int code);
void				init_signal_handler(void);
/*
**		BUILTINS
*/
int					ft_env(t_command *cmd, char **env);
void				ft_pwd(void);
void				ft_echo(t_command *ptr);
void				ft_cd(t_data *data, t_command *ptr);
void				ft_export(t_data *data, t_command *ptr);
void				ft_unset(t_data *data, t_command *ptr);
/*
**		ENV
*/
char				**get_env(char **env);
char				*get_env_var(char **env, char *name);
t_bool				set_env_var(char **env, char *name, char *variable);
/*
**		REDIRECTIONS
*/
void				handle_redir( t_data *data, t_command *cmd, t_redir *redir);
void				reset_redir(t_redir *stdin, t_redir *stdout);
/*
**		PIPES
*/
void				handle_pipes(t_data *data, t_command *cmd, t_pipe *pipe);
/*
**		UTILS
*/
void				ft_puterror(char *str1, char *str2, char *str3);
int					ft_isblank(char c);
int					ft_search(char c, char *str);
int					ft_indexof(char *str, char c);
int					ft_strisdigit(char *str);
int					tab_str_len(char **tab);
void				ft_error_min_max(t_data *data, t_command *cmd,
						unsigned long long res);
int					find_end(char *cmd, int i, char *sep);
int					find_start(char *cmd, int i, char *sep);
int					count_command(char *cmd);
int					skip_quotes(char const *str, int i);
char				*fill_tokens_utils_return(char *cmd, int *start, int *i);
char				*fill_tokens_utils(char *cmd, int *start, int *i);
t_command			*ft_create_struct(char *tokens);
int					multiple_commands(char **tokens);
int					ft_set_redir_utils(char *token, t_redir *redir,
						t_redir_type type);
/*
**		get_env_array_utils
*/
int					skip_env(char const *str, int i);
int					ft_norme_again(char const *str, int *i, int len);
char				*fill_env_array_utils(char const *str, char **env,
						int *env_len, int *i);
char				*fill_env_array(char const *str, char **env,
						int *env_len, int *i);
/*
**		get_new_str_utils
*/
void				skip_newstr(char const *str, char *new_str, int *i,
						int *j);
int					skip_env_name(char const *str, int i);
void				copy_env_value(char *new_str, char **env_array, int *k,
						int *j);
int					is_env_name(char const *str, int i);
void				init_normed_int(int *i, int *j, int *k);
/*
**		ERROR HANDLING
*/
int					check_command(t_data *data);
void				handle_error(t_data *data);
int					check_quotes_error(t_data *data, char *command);
int					check_error(t_data *data, char ***tokens);
int					check_semicolons_error(t_data *data, char *command);
int					check_empty_command(t_data *data, char *command);
int					check_syntax_error(t_data *data, char *command);
int					skip_sc_err_q(char *command, int i);
void				set_sc_error(t_data *data, char *command, int i);
int					check_missquotes(char *command, int i);
int					set_q_error(t_data *data);
/*
**		FREE
*/
void				free_tab_str(char **tab);
void				free_tokens(char ***tokens);
void				free_parser(t_command **parser);
void				free_lexer(t_data *data);

#endif
