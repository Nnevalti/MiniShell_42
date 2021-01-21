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

#include "../include/minishell.h"

void	prompt(char *my_prompt)
{
	char	buffer[MAX_PATH_LENGTH];

	getcwd(buffer, MAX_PATH_LENGTH);
	ft_putstr_fd("\e[1m\e[32m", 2);
	ft_putstr_fd(my_prompt, 2);
	ft_putstr_fd("@minishell:", 2);
	ft_putstr_fd("\e[94m", 2);
	ft_putstr_fd(buffer, 2);
	ft_putstr_fd( "\e[39m$> \e[0m", 2);
}

void	handle_exit(int signo)
{
	EXIT_CODE = 130;
	exit(1);
}

// void	run_exec(char *command, char **argv, char **env, int *pipes, int index)
// {
// 	char	**paths;
// 	int		i;
// 	int		status;
// 	char	*tmp;
// 	char	*str;
//
// 	if (!access(command, X_OK))
// 	{
// 		if (fork() == 0)
// 		{
// 			printf("pipe(pipes + %d);\n", 2 * index);
// 			// pipe(pipes + 2 * index);
//
// 			if (index > 0)
// 			{
// 				printf("dup2(pipes[%d], 0);\n", 2 * (index - 1));
// 				dup2(pipes[2 * (index - 1)], 0);
// 			}
//
// 			if (pipes[index + 1])
// 			{
// 				printf("dup2(pipes[%d], 1);\n", 1 + 2 * index);
// 				dup2(pipes[1 + 2 * index], 1);
//
// 			}
// 			execve(command, argv, env);
// 		}
// 		else
// 		{
// 			signal(SIGINT, SIG_IGN);
// 			wait(&status);
// 			EXIT_CODE = WEXITSTATUS(status);
// 			signal(SIGINT, &handle_exit);
// 		}
//
// 	}
// 	else
// 	{
// 		paths = ft_split(get_env_var(env, "PATH"), ':');
// 		i = 0;
// 		while (paths[i])
// 		{
// 			tmp = ft_strjoin(paths[i], "/");
// 			str = ft_strjoin(tmp, command);
// 			free(tmp);
// 			if (!access(str, X_OK))
// 			{
// 				if (fork() == 0)
// 				{
// 					printf("Index: %d\n", index);
// 					pipe_io(pipes, index);
// 					execve(str, argv, env);
// 				}
// 				else
// 				{
// 					// close_pipes(pipes);
// 					signal(SIGINT, SIG_IGN);
// 					wait(&status);
// 					printf("Index %d finished\n", index);
// 					EXIT_CODE = WEXITSTATUS(status);
// 					// printf("status : %d, %d\n", status, WEXITSTATUS(status));
// 					// printf("PARENT: %d\n", EXIT_CODE);
// 					signal(SIGINT, &handle_exit);
// 				}
// 				return ;
// 			}
// 			else
// 				EXIT_CODE = 126;
// 			free(str);
// 			i++;
// 		}
// 		printf("command not found: %s\n", command);
// 		EXIT_CODE = 127;
// 	}
// }

// int		run_command(char *command, char ***env)
// {
// 	char	**tokens;
// 	char	**splitted;
// 	int		*pipes;
// 	int		i;
//
// 	tokens = ft_split(command, '|');
// 	pipes = init_pipes(tokens);
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		// close(pipes[0]);
// 		// close(pipes[1]);
// 		// close(pipes[2]);
// 		// close(pipes[3]);
// 		printf("check (delete in main) : %d: %s\n", i, tokens[i]);
// 		splitted = ft_split(tokens[i], ' ');
//
// 		if (!ft_strcmp(splitted[0], "echo"))
// 			ft_echo(*env, tokens[i]);
// 		else if (!ft_strcmp(splitted[0], "env"))
// 			ft_env(*env);
// 		else if (!ft_strcmp(splitted[0], "cd"))
// 			ft_cd(splitted[1]);
// 		else if (!ft_strcmp(splitted[0], "pwd"))
// 			ft_pwd();
// 		else if (!ft_strcmp(splitted[0], "export"))
// 			ft_export(env, splitted);
// 		else if (!ft_strcmp(splitted[0], "unset"))
// 			ft_unset(env, splitted);
// 		else if (!ft_strcmp(splitted[0], "exit"))
// 		{
// 			free_tab_str(*env);
// 			free_tab_str(splitted);
// 			free_tab_str(tokens);
// 			exit(0);
// 		}
// 		else
// 			run_exec(splitted[0], splitted, *env, pipes, i);
// 		free_tab_str(splitted);
// 		i++;
// 	}
// 	printf("This is just a check, gotta delete it later (main)!\n");
// 	free(pipes);
// 	free_tab_str(tokens);
// 	return (TRUE);
// }

// void	init_signal_handler(void)
// {
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, signal_handler);
// }

int		main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;
	char	*new_command;

	data = init_data(env);

	while (42)
	{
		// init_signal_handler();
		prompt(data->prompt);
		get_next_line(0, &data->command);
		printf("USER COMMAND: %s\n", data->command);

		// LEXER
		handle_env(data);
		data->tokens = ft_lexer(data);
		if (data->error->errno)
			handle_error(data);
		else
		{
			// printf("\nLEXER :\n");
			// for (int j = 0; data->tokens[j]; j++)
			// 	printf("TOKEN %d %s\n", j, data->tokens[j]);
			// printf("\n");
			// free(data->new_command);

			// FREE COMMAND
			free(data->command);

			// PARSER
			data->parser = ft_parser(data->tokens);

			// FREE LEXER
			free_tab_str(data->tokens);

			// EXECUTOR
			ast_exec(data);

			// FREE PARSER
			free_ast(data->parser);
		}
	}
}
