#include "../include/minishell.h"

void	reset_redir(t_redir *redir)
{
	if (redir->type == REDIRECT_STDOUT || redir->type == APPEND_STDOUT)
		dup2(redir->saved_fd,1);
	else if (redir->type == REDIRECT_STDIN)
		dup2(redir->saved_fd,0);
	close(redir->saved_fd);
	return ;
}

void	handle_redir(t_redir *redir, t_data *data)
{
	int fd;
	t_redir *current;
	int pid;
	int status;

	char *const argv[]={"echo","lol","lol",NULL};
	const char *pathname = "/usr/bin/echo";

	current = redir;
	while (current)
	{
		// printf("current->str [%s]\n",current->str);
		if (current->type == REDIRECT_STDOUT)
		{
			current->saved_fd = dup(1);

			fd = open(current->str, O_WRONLY | O_CREAT, 0777);
			dup2(fd,1);
			close(fd);
		}
		else if (current->type == APPEND_STDOUT)
		{
			current->saved_fd = dup(1);

			fd = open(current->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2(fd,1);
			close(fd);
		}
		else if (current->type == REDIRECT_STDIN)
		{
			current->saved_fd = dup(0);

			fd = open(current->str, O_RDONLY, 0777);
			dup2(fd,0);
			close(fd);
		}
		if((pid = fork()) == 0)
		{
			execve("/usr/bin/echo",argv,data->my_env);
			exit(1);
		}
		else
		{
			wait(&status);
			reset_redir(current);
		}

		current = current->next;
	}
	return ;
}
