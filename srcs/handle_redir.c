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

void	handle_bad_fd(t_data *data, char *str)
{
	char *tmp;

	tmp = ft_strdup("Minishell: no such file or directory: ");
	// free(data->error->value);
	data->error->value = ft_strjoin(tmp, str);
	data->error->errno = FD;
	free(tmp);
}

void	handle_redir( t_data *data, t_command *cmd, t_redir *redir)
{
	int fd;
	t_redir *current;

	current = redir;
	while (current)
	{
		if (current->type == REDIRECT_STDOUT)
		{
			current->saved_fd = dup(1);

			if ((fd = open(current->str, O_WRONLY | O_CREAT, 0777)) == -1)
			{
				handle_bad_fd(data, current->str);
				return ;
			}
			else
			{
				dup2(fd,1);
				close(fd);
			}
		}
		else if (current->type == APPEND_STDOUT)
		{
			current->saved_fd = dup(1);

			if ((fd = open(current->str, O_WRONLY | O_CREAT | O_APPEND, 0777) == -1))
			{
				handle_bad_fd(data, current->str);
				return ;
			}
			else
			{
				dup2(fd,1);
				close(fd);
			}
		}
		else if (current->type == REDIRECT_STDIN)
		{
			current->saved_fd = dup(0);

			if ((fd = open(current->str, O_RDONLY, 0777)) == -1)
			{
				handle_bad_fd(data, current->str);
				return ;
			}
			else
			{
				dup2(fd,0);
				close(fd);
			}
		}
		exec_cmd(data, cmd);
		reset_redir(current);

		current = current->next;
	}
	return ;
}
