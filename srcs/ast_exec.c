#include "../include/minishell.h"

// void	run_exec(char *command, char **argv, char **env, , int index)
// {
// 	char	**paths;
// 	int		i;
// 	int		status;
// 	char	*tmp;
// 	char	*str;
// 	int *pipes;
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

int		run_command(t_data *data, t_tree *ptr)
{

	if (!ft_strcmp(ptr->command, "echo"))
		ft_echo(ptr);
	else if (!ft_strcmp(ptr->command, "env"))
		ft_env(data->my_env);
	else if (!ft_strcmp(ptr->command, "cd"))
		ft_cd(ptr);
	else if (!ft_strcmp(ptr->command, "pwd"))
		ft_pwd();
	// else if (!ft_strcmp(ptr->command, "export"))
	// 	ft_export(data);
	// else if (!ft_strcmp(ptr->command, "unset"))
	// 	ft_unset(data->my_env);
	// else if (!ft_strcmp(ptr->command, "exit"))
	// {
	// 	free_tab_str(*env);
	// 	free_tab_str(splitted);
	// 	free_tab_str(tokens);
	// 	exit(0);
	// }
	// else
	// 	run_exec(splitted[0], splitted, *env, i);
	// free_tab_str(splitted);
	// i++;
	return (TRUE);
}

void	analyze_struct(t_data *data, t_tree *ptr)
{
	if (ptr->type == PIPE)
	{
		printf("ouverture du chemin de disucssion entre left et right\n");
	}
	if (ptr->type == COMMAND)
	{
		run_command(data, ptr);
	}
	if (ptr->type == REDIR)
	{
		if (ptr->redir_type == REDIRECT_STDOUT)
			printf("REDIR_STDOUT: %s\n", ptr->file);
		else if (ptr->redir_type == APPEND_STDOUT)
			printf("APP_STDOUT: %s\n", ptr->file);
		else if (ptr->redir_type == REDIRECT_STDIN)
			printf("REDIR_STDIN: %s\n", ptr->file);
	}
	return ;
}

void	analyze_end_struct(t_tree *ptr)
{
	if (ptr->type == PIPE)
	{
		printf("fermeture du chemin de disucssion entre left et right\n");
	}
	if (ptr->type == REDIR)
	{
		if (ptr->redir_type == REDIRECT_STDOUT)
			printf("REDIR_STDOUT close\n");
		else if (ptr->redir_type == APPEND_STDOUT)
			printf("APP_STDOUT close\n");
		else if (ptr->redir_type == REDIRECT_STDIN)
			printf("REDIR_STDIN close\n");
	}
	return ;
}

void recursive(t_data *data, t_tree *ptr)
{
	int		i;

	i = 0;
	printf("%d %s ", ptr->type, ptr->command);
	if (ptr->options != NULL)
	{
		while (ptr->options[i])
		{
			printf("%s ", ptr->options[i]);
			i++;
		}
	}
	printf("\n");
	// start
	analyze_struct(data, ptr);
	if (ptr->left != NULL)
	{
		recursive(data, ptr->left);
		if (ptr->right != NULL)
		{
			recursive(data, ptr->right);
			analyze_end_struct(ptr);
		}
	}
	else if (ptr->right != NULL)
		printf("WTF error\n");

	return ;
}

void ast_exec(t_data *data)
{
	printf("\nIN AST_EXEC\n");
	recursive(data, data->parser);
	printf("WE LEAVE AST_EXEC\n\n");
}
