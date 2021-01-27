#include "../include/minishell.h"

void 	signal_handler(int code)
{
	if (g_pid == 0)
	{
		if (code == SIGQUIT)
			write(2,"\b\b \b\b",6);
		else
		{
			// g_exit_status = 130;
			// ft_strlcpu(g_exit_status_buffer,"130",4)
			write(2,"\n",1);
			prompt();
		}
	}
	else
		kill(g_pid,code);
	g_pid = 0;
	return ;
}
