#include "../include/minishell.h"

void	run_exec(t_data *data, t_command *cmd)
{
	int		pid;
	char	**paths;
	int		i;
	int		status;
	char	*tmp;
	char	*str;
	struct stat buffer;

	if (!(stat(cmd->cmd, &buffer)))
	{
		if ((pid = fork()) == 0)
		{
			execve(cmd->cmd, cmd->opt_tab, data->my_env);
			exit(1);
		}
		else
		{
			// signal(SIGINT, SIG_IGN);
			wait(&status);
			// EXIT_CODE = WEXITSTATUS(status);
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
			str = ft_strjoin(tmp, cmd->cmd);
			free(tmp);
			if (!(stat(str, &buffer)))
			{
				if ((pid = fork()) == 0)
				{
					execve(str, cmd->opt_tab, data->my_env);
					exit(1);
				}
				else
				{
					// signal(SIGINT, SIG_IGN);
					wait(&status);
					// EXIT_CODE = WEXITSTATUS(status);
					// signal(SIGINT, &handle_exit);
				}
				free(str);
				return ;
			}
			// else
			// 	EXIT_CODE = 126;
			free(str);
			i++;
		}
		printf("command not found: %s\n", cmd->cmd); // ecrire dans le stderr
		// EXIT_CODE = 127;
	}
}

void	exec_cmd(t_data *data, t_command *cmd)
{
	// if (!ft_strcmp(cmd->cmd, "echo"))
	// 	ft_echo(ptr);
	// else if (!ft_strcmp(cmd->cmd, "env"))
	// 	ft_env(data->my_env);
	// else if (!ft_strcmp(cmd->cmd, "cd"))
	// 	ft_cd(data, ptr);
	// else if (!ft_strcmp(cmd->cmd, "pwd"))
	// 	ft_pwd();
	// else if (!ft_strcmp(cmd->cmd, "export"))
	// 	ft_export(data, ptr);
	// else if (!ft_strcmp(cmd->cmd, "unset"))
	// 	ft_unset(data, ptr);
	// else
	if (!ft_strcmp(cmd->cmd, "exit"))
			handle_exit(data);
	else
		run_exec(data, cmd);
	// DETECT ERROR COMMAND
	return ;
}
