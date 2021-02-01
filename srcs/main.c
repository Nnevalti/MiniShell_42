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

void	prompt()
{
	char	buffer[MAX_PATH_LENGTH];

	getcwd(buffer, MAX_PATH_LENGTH);
	ft_putstr_fd("\e[1m\e[32m", 2);
	ft_putstr_fd(g_prompt, 2);
	ft_putstr_fd("@minishell:", 2);
	ft_putstr_fd("\e[94m", 2);
	ft_putstr_fd(buffer, 2);
	ft_putstr_fd( "\e[39m$> \e[0m", 2);
}

int		ft_strisdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_error_min_max(t_data *data, t_command *cmd, unsigned long long res)
{
	if (cmd->opt_tab[1][0] == '-')
	{
		if (((res * -1) - 1) > 9223372036854775807ULL)
		{
			errno = 2;
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(cmd->opt_tab[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
	}
	else
	{
		if (res > 9223372036854775807ULL)
		{
			errno = 2;
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(cmd->opt_tab[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
	}
}


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
		{
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(cmd->opt_tab[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);

		}
		free_parser(data->parser);
	}
	free_before_exit(data);
	write(1,"exit\n",5);
	exit(errno);
}

void	init_signal_handler(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, kill_prg);
}

int		main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;
	int test;

	data = init_data(env);
	init_signal_handler();
	g_prompt = ft_strdup(get_env_var(data->my_env, "USER"));
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
		if (check_empty_command(data, data->command) == -1
		|| check_quotes_error(data, data->command) == -1
		|| check_semicolons_error(data, data->command) == -1
		|| check_syntax_error(data, data->command) == -1)
			handle_error(data);
		else
		{
			// LEXER
			data->tokens = ft_lexer(data);

			// FREE COMMAND
			free(data->command);
			if (check_error(data, data->tokens) == -1)
				handle_error(data);
			else
			{
				// PARSER
				data->parser = ft_parser(data);
				//
				// FREE LEXER
				free_lexer(data);

				// EXECUTOR
				ft_executor(data);

				// printf("FREE LEXER\n");
				// FREE PARSER
				// if (!ft_strcmp(data->parser[0]->cmd, "exit"))
					// handle_exit(data);
				free_parser(data->parser);
			}
		}
	}
}
