#include "../include/minishell.h"

// void	run_exec(char *command, char **argv, char **env, , int index)
void	run_exec(t_data *data, t_tree *ptr)
{
	char	**paths;
	int		i;
	int		status;
	char	*tmp;
	char	*str;

	if (!access(ptr->command, X_OK))
	{
		if (fork() == 0)
		{
			execve(str, ptr->options, data->my_env);
		}
		else
		{
			// signal(SIGINT, SIG_IGN);
			wait(&status);
			EXIT_CODE = WEXITSTATUS(status);
			// signal(SIGINT, &handle_exit);
		}

	}
	else
	{
		paths = ft_split(get_env_var(data->my_env, "PATH"), ':');
		i = 0;
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			str = ft_strjoin(tmp, ptr->command);
			free(tmp);
			if (!access(str, X_OK))
			{
				if (fork() == 0)
				{
					execve(str, ptr->options, data->my_env);
				}
				else
				{
					// signal(SIGINT, SIG_IGN);
					wait(&status);
					EXIT_CODE = WEXITSTATUS(status);
					// signal(SIGINT, &handle_exit);
				}
				free(str);
				return ;
			}
			else
				EXIT_CODE = 126;
			free(str);
			i++;
		}
		printf("command not found: %s\n", ptr->command);
		EXIT_CODE = 127;
	}
}

int		run_command(t_data *data, t_tree *ptr)
{

	if (!ft_strcmp(ptr->command, "echo"))
		ft_echo(ptr);
	else if (!ft_strcmp(ptr->command, "env"))
		ft_env(data->my_env);
	else if (!ft_strcmp(ptr->command, "cd"))
		ft_cd(data, ptr);
	else if (!ft_strcmp(ptr->command, "pwd"))
		ft_pwd();
	// else if (!ft_strcmp(ptr->command, "export"))
	// 	ft_export(data);
	// else if (!ft_strcmp(ptr->command, "unset"))
	// 	ft_unset(data->my_env);
	else if (!ft_strcmp(ptr->command, "exit"))
	{
			free_tab_str(data->my_env);
			free(data->prompt);
			free_ast(data->parser);
			exit (0);
	}
	else
		run_exec(data, ptr);
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
