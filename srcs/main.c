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

void	handle_exit(int signo)
{
	EXIT_CODE = 130;
	exit(1);
}

void	run_exec(char *command, char **argv, char **env)
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
		{
			signal(SIGINT, SIG_IGN);
			wait(&status);
			EXIT_CODE = WEXITSTATUS(status);
			signal(SIGINT, &handle_exit);
		}

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
				{
					// printf("CHILD: %d\n", EXIT_CODE);
					execve(str, argv, env);
				}
				else
				{
					signal(SIGINT, SIG_IGN);
					wait(&status);
					EXIT_CODE = WEXITSTATUS(status);
					// ft_printf("status : %d, %d\n", status, WEXITSTATUS(status));
					// printf("PARENT: %d\n", EXIT_CODE);
					signal(SIGINT, &handle_exit);
				}
				return ;
			}
			else
				EXIT_CODE = 126;
			free(str);
			i++;
		}
		ft_printf("command not found: %s\n", command);
		EXIT_CODE = 127;
	}
}

int		run_command(char *command, char ***env)
{
	char	**splitted;
	char	**tokens;
	int		fd;
	char	*str;
	int		saved_stdout;

	if (ft_indexof(command, '>') >= 0)
	{
		tokens = ft_split(command, '>');
		// printf("%s | %s\n", tokens[0], tokens[1]);
		str = ft_strtrim(tokens[1], " ");
		fd = open(str, O_WRONLY | O_CREAT, 0777);
		free(str);
		saved_stdout = dup(1);
		dup2(fd, 1);
		close(fd);
		splitted = ft_split(tokens[0], ' ');
	}
	else
		splitted = ft_split(command, ' ');

	// parser la commande par rapport au espacccce et vérifier avec strcmp ?
	if (!ft_strcmp(splitted[0], "echo"))
		ft_echo(*env, splitted);
	else if (!ft_strcmp(splitted[0], "env"))
		ft_env(*env);
	else if (!ft_strcmp(splitted[0], "cd"))
		ft_cd(splitted[1]);
	else if (!ft_strcmp(splitted[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(splitted[0], "export"))
		ft_export(env, splitted);
	else if (!ft_strcmp(splitted[0], "unset"))
		ft_unset(env, splitted);
	else if (!ft_strcmp(splitted[0], "exit"))
	{
		free_tab_str(*env);
		free_tab_str(splitted);
		exit(0);
	}
	else
		run_exec(splitted[0], splitted, *env);
	free_tab_str(splitted);
	if (ft_indexof(command, '>') >= 0)
	{
		ft_printf("test\n");
		dup2(saved_stdout, 1);
		close(saved_stdout);
	}
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	int		i;
	int		j;
	char	**my_env;
	char	*command;
	char 	**splitted;
	char	**commands;

	my_env = get_env(env);
	signal(SIGINT, &handle_exit);
	while (42)
	{
		j = 0;
		prompt(env);
		get_next_line(0, &command);
		commands = ft_split_command_line(command);
		while (commands[j])
		{
			// ft_printf("commands[%d] = %s\n", j, commands[j]);
			run_command(commands[j], &my_env);
			j++;
		}
		free(command);
		free_tab_str(commands);
	}
}
