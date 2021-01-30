/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 15:00:05 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/15 16:47:56 by tfevrier         ###   ########.fr       */
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

void	handle_exit(t_data *data/*int signo*/)
{

	// EXIT_CODE = 130;
	free_tab_str(data->my_env);
	free(g_prompt);
	free(data->error);
	free(data);
	write(1, "exit\n", 5);
	exit(1);
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
		if (get_next_line(0, &data->command) == 0)
		{
			free(data->command);
			handle_exit(data);
		}
		// printf("USER COMMAND : [%s]\n", data->command);
		if (check_quotes_error(data, data->command) == -1
		|| check_semicolons_error(data, data->command) == -1
		|| check_empty_command(data, data->command) == -1
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
