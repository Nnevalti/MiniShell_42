#include "../include/minishell.h"

void	fork_exec(t_data *data, t_command *cmd, char *str)
{
	int		status;
	int		pid;

	if ((pid = fork()) == 0)
	{
		printf("IN FORK str [%s]\n",str);
		for (int i = 0; cmd->opt_tab[i]; i++)
			printf("IN FORK opt_tab[%d]: [%s]\n",i, cmd->opt_tab[i]);
		if (cmd->p_handled && cmd->pipe->in)
		{
			dup2(cmd->pipe->stdin[0], 0);
			close(cmd->pipe->stdin[1]);
		}
		if (cmd->p_handled && cmd->pipe->out)
		{
			dup2(cmd->pipe->stdout[1], 1);
			close(cmd->pipe->stdout[0]);
		}
		execve(str, cmd->opt_tab, data->my_env);
		exit(1);
	}
	else
	{
		// signal(SIGINT, SIG_IGN);
		wait(&status);
		if (cmd->p_handled && cmd->pipe->in)
			close(cmd->pipe->stdin[0]);
		if (cmd->p_handled && cmd->pipe->out)
			close(cmd->pipe->stdout[1]);
		// EXIT_CODE = WEXITSTATUS(status);
		// signal(SIGINT, &handle_exit);
	}
}

void	run_exec(t_data *data, t_command *cmd)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*str;
	struct stat buffer;

	if (!(stat(cmd->cmd, &buffer)))
		fork_exec(data, cmd, cmd->cmd);
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
				fork_exec(data, cmd, str);
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
		printf("command not found: %s\n", cmd->cmd); // ecrire dans le stderr
		// EXIT_CODE = 127;
	}
}

void	exec_cmd(t_data *data, t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(data->my_env);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		ft_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "exit"))
			handle_exit(data);
	else
		run_exec(data, cmd);
	// DETECT ERROR COMMAND
	return ;
}
