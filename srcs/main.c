/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:05:54 by vdescham          #+#    #+#             */
/*   Updated: 2021/02/01 01:05:56 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_before_exit(t_data *data)
{
	free_tab_str(data->my_env);
	free(g_prompt);
	free(data->error);
	free(data);
	return ;
}

void	handle_exit(t_data *data, t_command *cmd)
{
	unsigned long long res;

	if (cmd && cmd->opt_tab)
	{
		if (cmd->opt_tab[1] && ft_strisdigit(cmd->opt_tab[1]))
		{
			if (cmd->opt_tab[2])
			{
				ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
				return ;
			}
			res = ft_atoi(cmd->opt_tab[1]);
			errno = res;
			ft_error_min_max(data, cmd, res);
		}
		else if (cmd->opt_tab[1])
			ft_puterror("Minishell: exit: ", cmd->opt_tab[1],
					": numeric argument required\n");
		free_parser(data->parser);
	}
	free_before_exit(data);
	write(1, "exit\n", 5);
	exit(errno);
}

void	minishell2(t_data *data)
{
	if (check_command(data) == -1)
		handle_error(data);
	else
	{
		data->tokens = ft_lexer(data);
		free(data->command);
		if (check_error(data, data->tokens) == -1)
			handle_error(data);
		else
		{
			data->parser = ft_parser(data);
			free_lexer(data);
			ft_executor(data);
			free_parser(data->parser);
		}
	}
}

void	minishell(t_data *data)
{
	while (42)
	{
		g_pid[0] = 0;
		g_pid[1] = 0;
		prompt();
		if ((get_next_line(0, &data->command) == 0))
		{
			free(data->command);
			handle_exit(data, NULL);
		}
		minishell2(data);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = init_data(env);
	init_signal_handler();
	g_prompt = ft_strdup(get_env_var(data->my_env, "USER"));
	minishell(data);
}
