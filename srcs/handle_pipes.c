#include "../include/minishell.h"

void	handle_pipes(t_data *data, t_command *cmd, t_pipe *pipes)
{
	t_command *next;

	next = cmd->next;
	if (pipes->out)
	{
		pipe(pipes->stdout);
		next->pipe->stdin[0] = pipes->stdout[0];
		next->pipe->stdin[1] = pipes->stdout[1];
	}
	cmd->p_handled = TRUE;
	printf("\nhandlepipe->stdin[0] = %d | pipe->stdin[1] = %d\n",cmd->pipe->stdin[0],cmd->pipe->stdin[1]);
	printf("handlepipe->stdout[0] = %d | pipe->stdout[1] = %d\n",cmd->pipe->stdout[0],cmd->pipe->stdout[1]);
	return ;
}
