#include "../include/minishell.h"

// void	run_exec(char *command, char **argv, char **env, , int index)

// void	handle_pipe(t_command *current)
// {
// 	if(current->pipe)
// 		pipe(fd);
// }

void	analyse_parser(t_command *cmd, t_data *data)
{
	t_command *current;
	char *path;
	// char *const argv[]={"echo","lol","lol",NULL};
	// const char *pathname = "/usr/bin/echo";

	current = cmd;
	while(current)
	{
		handle_env(current, data);
		printf("current->cmd %s\n",current->cmd);
		printf("current->opt %s\n",current->opt);
		// handle_quotes(current, data);
		// handle_redir(current);
		// handle_pipes(current);
		// execve("/usr/bin/echo",argv,data->my_env);
		current = current->next;
	}
}
void	ft_executor(t_data *data)
{
	printf("\nIN EXECUTOR\n");
	int i;

	i = 0;
	while(data->parser[i])
	{
		analyse_parser(data->parser[i], data);
		i++;
	}
	printf("WE LEAVE EXECUTOR\n\n");
}
