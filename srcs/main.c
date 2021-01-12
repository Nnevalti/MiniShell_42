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
	write(1, "\e[1m\e[32m", 9);
	write(1, get_env_var(env, "USER"), ft_strlen(get_env_var(env, "USER")));
	write(1, "@minishell:", 11);
	write(1, "\e[94m", 5);
	write(1, buffer, ft_strlen(buffer));
	write(1, "\e[39m$> \e[0m", 12);

}

void	handle_exit(int signo)
{
	EXIT_CODE = 130;
	exit(1);
}

void	run_exec(char *command, char **argv, char **env, int *pipes, int index)
{
	char	**paths;
	int		i;
	int		status;
	char	*tmp;
	char	*str;

	if (!access(command, X_OK))
	{
		if (fork() == 0)
		{
			printf("pipe(pipes + %d);\n", 2 * index);
			// pipe(pipes + 2 * index);

			if (index > 0)
			{
				printf("dup2(pipes[%d], 0);\n", 2 * (index - 1));
				dup2(pipes[2 * (index - 1)], 0);
			}

			if (pipes[index + 1])
			{
				printf("dup2(pipes[%d], 1);\n", 1 + 2 * index);
				dup2(pipes[1 + 2 * index], 1);

			}
			execve(command, argv, env);
		}
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
					printf("Index: %d\n", index);
					pipe_io(pipes, index);
					execve(str, argv, env);
				}
				else
				{
					// close_pipes(pipes);
					signal(SIGINT, SIG_IGN);
					wait(&status);
					printf("Index %d finished\n", index);
					EXIT_CODE = WEXITSTATUS(status);
					// printf("status : %d, %d\n", status, WEXITSTATUS(status));
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
		printf("command not found: %s\n", command);
		EXIT_CODE = 127;
	}
}

int		run_command(char *command, char ***env)
{
	char	**tokens;
	char	**splitted;
	int		*pipes;
	int		i;

	tokens = ft_split(command, '|');
	pipes = init_pipes(tokens);
	i = 0;
	while (tokens[i])
	{
		// close(pipes[0]);
		// close(pipes[1]);
		// close(pipes[2]);
		// close(pipes[3]);
		printf("check (delete in main) : %d: %s\n", i, tokens[i]);
		splitted = ft_split(tokens[i], ' ');

		if (!ft_strcmp(splitted[0], "echo"))
			ft_echo(*env, tokens[i]);
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
			free_tab_str(tokens);
			exit(0);
		}
		else
			run_exec(splitted[0], splitted, *env, pipes, i);
		free_tab_str(splitted);
		i++;
	}
	printf("This is just a check, gotta delete it later (main)!\n");
	free(pipes);
	free_tab_str(tokens);
	return (TRUE);
}

int		main(int argc, char **argv, char **env)
{
	int		i;
	char	**my_env;
	char	*command;
	char	**commands;

	my_env = get_env(env);
	signal(SIGINT, &handle_exit);
	while (42)
	{
		prompt(env);
		get_next_line(0, &command);
		printf("command: %s\n", command);
// LEXER
		commands = ft_lexer(command);
		for (int j = 0; commands[j]; j++)
			printf("commands %d %s\n", j, commands[0]);
// PARSER

		// i = 0;
		// while (commands[i]) // execute every command
		// {
		// 	// printf("commands[%d] = %s\n", i, commands[i]);
		// 	run_command(commands[i], &my_env);
		// 	i++;
		// }
		// free(command);
		// free_tab_str(commands);
// FREE LEXER
// FREE PARSER
	}
}
