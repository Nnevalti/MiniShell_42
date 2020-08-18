/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:00:05 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/15 16:47:56 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **env)
{
	char	buffer[MAX_PATH_LENGTH];

	getcwd(buffer, MAX_PATH_LENGTH);
	ft_printf("\e[1m\e[32m");
	ft_printf("%s@minishell:", get_env_var(env, "USER"));
	ft_printf("\e[94m%s \e[39m$> \e[0m", buffer);
}

void	run_command(char *command, char **argv, char **env)
{
	char	**paths;
	int		i;
	int		status;
	char	*tmp;
	char	*str;

	if (!access(command, X_OK))
	{
		if (fork() == 0)
			execve(command, argv, env);
		else
			wait(&status);
	}
	else
	{
		paths = ft_split(get_env_var(env, "PATH"), ':');
		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			str = ft_strjoin(tmp, command);
			free(tmp);
			if (!access(str, X_OK))
			{
				if (fork() == 0)
					execve(str, argv, env);
				else
					wait(&status);
			}
			free(str);
			i++;
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	int		i;
	char	**my_env;
	char	*command;
	char 	**splitted;

	my_env = get_env(env);

	// signal(SIGINT, SIG_IGN);
	while (42)
	{
		prompt(env);
		get_next_line(0, &command);
		splitted = ft_split(command, ' ');
		// parser la commande par rapport au espacccce et vérifier avec strcmp ?
		if (!ft_strcmp(splitted[0], "echo"))
			ft_echo(my_env, splitted);
		else if (!ft_strcmp(splitted[0], "env"))
			ft_env(my_env);
		else if (!ft_strcmp(splitted[0], "cd"))
			ft_cd(splitted[1]);
		else if (!ft_strcmp(splitted[0], "pwd"))
			ft_pwd();
		else if (!ft_strcmp(splitted[0], "export"))
			ft_export(&my_env, splitted);
		else if (!ft_strcmp(splitted[0], "unset"))
			ft_unset(&my_env, splitted);
		else if (!ft_strcmp(splitted[0], "exit"))
		{
			free_env(my_env);
			exit(0);
		}
		else
			run_command(splitted[0], splitted, my_env);
		free(command);
		i = 0;
		while (splitted[i])
			free(splitted[i++]);
		free(splitted);
	}
}
