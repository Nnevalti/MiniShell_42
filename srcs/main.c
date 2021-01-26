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

void	prompt(char *my_prompt)
{
	char	buffer[MAX_PATH_LENGTH];

	getcwd(buffer, MAX_PATH_LENGTH);
	ft_putstr_fd("\e[1m\e[32m", 2);
	ft_putstr_fd(my_prompt, 2);
	ft_putstr_fd("@minishell:", 2);
	ft_putstr_fd("\e[94m", 2);
	ft_putstr_fd(buffer, 2);
	ft_putstr_fd( "\e[39m$> \e[0m", 2);
}

void	handle_exit(t_data *data/*int signo*/)
{

	// EXIT_CODE = 130;
	free_parser(data->parser);
	free_tab_str(data->my_env);
	free(data->prompt);
	free(data->error);
	free(data);
	exit(1);
}

// void	init_signal_handler(void)
// {
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, signal_handler);
// }

int		main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;

	data = init_data(env);

	while (42)
	{
		// init_signal_handler();
		prompt(data->prompt);
		get_next_line(0, &data->command);
		printf("USER COMMAND: %s\n", data->command);
		if (check_quotes_error(data, data->command) == -1)
		{
			handle_error(data);
		}
		else
		{
			// LEXER
			// handle_env(data);
			data->tokens = ft_lexer(data);

			// DEBUGGING
			printf("\nLEXER :\n");
			for(int i = 0; data->tokens[i]; i++)
				for(int j = 0; data->tokens[i][j]; j++)
					printf("TOKENS[%d][%d] : [%s]\n",i,j,data->tokens[i][j]);
			// END DEBUGGING

			// FREE COMMAND
			free(data->command);
			if (check_error(data, data->tokens) == -1)
			{
				handle_error(data);
			}
			else
			{
				// PARSER
				data->parser = ft_parser(data);
				//
				// FREE LEXER
				free_lexer(data);

				// EXECUTOR
				ft_executor(data);

				printf("FREE LEXER\n");
				// FREE PARSER
				if (!ft_strcmp(data->parser[0]->cmd, "exit"))
					handle_exit(data);
				free_parser(data->parser);
			}
		}
	}
}
