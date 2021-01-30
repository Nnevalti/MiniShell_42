#include "../include/minishell.h"

void	run_exec(t_data *data, t_command *cmd)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*str;
	struct stat buffer;

	if ((g_pid[0] = fork()) == 0)
	{
		if (!(stat(cmd->cmd, &buffer)))
			execve(cmd->cmd, cmd->opt_tab, data->my_env);
		else
		{
			paths = ft_split(get_env_var(data->my_env, "PATH"), ':');
			i = 0;
			while (paths[i])
			{
				tmp = ft_strjoin(paths[i], "/");
				str = ft_strjoin(tmp, cmd->cmd);
				free(tmp);
				if (!(stat(str, &buffer)))
				{
					execve(str, cmd->opt_tab, data->my_env);
					free(str);
					free_tab_str(paths);
					return ;
				}
				// else
				// 	EXIT_CODE = 126;
				free(str);
				i++;
			}
			free_tab_str(paths);
			ft_putstr_fd("command not found: ", 2); // ecrire dans le stderr
			ft_putstr_fd(cmd->cmd, 2); // ecrire dans le stderr
			ft_putstr_fd("\n", 2); // ecrire dans le stderr
			// EXIT_CODE = 127;
		}
		exit(1);
	}
	else
	{
		waitpid(g_pid[0], NULL, 0);
	}
	return ;
}

void	what_cmd(t_data *data, t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(data->my_env);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "exit"))
	{
		free_parser(data->parser);
		handle_exit(data);
	}
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(data, cmd);
	else
		run_exec(data, cmd);
	return ;
}

void	fork_exec(t_data *data, t_command *cmd)
{
	int		status;

	if ((g_pid[1] = fork()) == 0)
	{
		if (cmd->p_handled && cmd->pipe->in && !cmd->last_stdin)
		{
			close(cmd->pipe->stdin[1]);
			dup2(cmd->pipe->stdin[0], 0);
		}
		if (cmd->p_handled && cmd->pipe->out && !cmd->last_stdout)
		{
			close(cmd->pipe->stdout[0]);
			dup2(cmd->pipe->stdout[1], 1);
		}
		what_cmd(data, cmd);
		exit(1);
	}
	else
	{
		// signal(SIGINT, SIG_IGN);
		if (cmd->p_handled && cmd->pipe->in)
		{
			close(cmd->pipe->stdin[0]);
			close(cmd->pipe->stdin[1]);
		}
		if (cmd->p_handled && cmd->pipe->out)
		{
			close(cmd->pipe->stdout[1]);
			close(cmd->pipe->stdout[0]);
		}
		// EXIT_CODE = WEXITSTATUS(status);
		// signal(SIGINT, &handle_exit);
	}
	waitpid(g_pid[1], NULL, 0);
	return ;
}

void	exec_cmd(t_data *data, t_command *cmd)
{
	if (cmd->p_handled)
		fork_exec(data, cmd);
	else
		what_cmd(data, cmd);
	// DETECT ERROR COMMAND
	return ;
}
