/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:03:56 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:03:58 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	find_in_path(t_data *data, t_command *cmd, struct stat buffer)
{
	int			i;
	char		**paths;
	char		*tmp;
	char		*str;

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
		}
		free(str);
		i++;
	}
	free_tab_str(paths);
	ft_puterror("command not found: ", cmd->cmd, "\n");
}

void	run_exec(t_data *data, t_command *cmd)
{
	int			status;
	struct stat	buffer;

	status = 0;
	if ((g_pid[0] = fork()) == 0)
	{
		if (!(stat(cmd->cmd, &buffer)))
			execve(cmd->cmd, cmd->opt_tab, data->my_env);
		else
		{
			find_in_path(data, cmd, buffer);
			exit(127);
		}
	}
	else
	{
		waitpid(g_pid[0], &status, 0);
		if (errno != 131 && errno != 130)
			errno = WEXITSTATUS(status);
	}
	return ;
}

void	what_cmd(t_data *data, t_command *cmd)
{
	errno = 0;
	if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(cmd, data->my_env);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->cmd, "export"))
		ft_export(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		handle_exit(data, cmd);
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
		open_pipe(cmd);
		what_cmd(data, cmd);
		exit(1);
	}
	else
		close_pipe(cmd);
	waitpid(g_pid[1], &status, 0);
	errno = status / 256;
	return ;
}

void	exec_cmd(t_data *data, t_command *cmd)
{
	if (cmd->p_handled)
		fork_exec(data, cmd);
	else
		what_cmd(data, cmd);
	return ;
}
