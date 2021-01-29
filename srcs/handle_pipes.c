#include "../include/minishell.h"

void	handle_pipes(t_data *data, t_command *cmd, t_pipe *pipes)
{
	t_command *next;

	next = cmd->next;

	if (pipes->out)
	{
		pipe(pipes->stdout);
		next->pipe->stdin[0] = dup(pipes->stdout[0]);
		next->pipe->stdin[1] = dup(pipes->stdout[1]);
	}
	cmd->p_handled = TRUE;
	return ;
}
