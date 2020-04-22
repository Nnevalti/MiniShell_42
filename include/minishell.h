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

int		ft_env(char **env);
void	ft_pwd(char **env);
void	ft_echo(char** splitted);
int		ft_indexof(char *str, char c);
char 	*get_env_var(char **env, char *name);

#endif
