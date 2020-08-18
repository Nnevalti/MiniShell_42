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
# include <sys/types.h>
# include <sys/wait.h>

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

# define MAX_PATH_LENGTH 4096

# define TRUE 1
# define FALSE 0

typedef int		t_bool;

int				ft_env(char **env);
void			ft_pwd(void);
void			ft_echo(char **env, char **splitted);
void			ft_cd(char *path);
void			ft_export(char ***env, char **splitted);
void			ft_unset(char ***env, char **splitted);

int				ft_indexof(char *str, char c);
char			**ft_split_command_line(char const *commands);

char			**get_env(char **env);
void			free_env(char **env);
char 			*get_env_var(char **env, char *name);
t_bool			set_env_var(char **env, char *name, char *variable);

#endif
