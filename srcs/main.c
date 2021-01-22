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

void	handle_exit(int signo)
{
	EXIT_CODE = 130;
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
	char	*new_command;

	data = init_data(env);

	while (42)
	{
		// init_signal_handler();
		prompt(data->prompt);
		get_next_line(0, &data->command);
		printf("USER COMMAND: %s\n", data->command);

		// LEXER
		// handle_env(data);
		data->tokens = ft_lexer(data);
		printf("TOKENS[0][0] : [%s]\n", data->tokens[0][0]);

		printf("\nLEXER :\n");
		for(int i = 0; data->tokens[i]; i++)
			for(int j = 0; data->tokens[i][j]; j++)
				printf("TOKENS[%d][%d] : [%s]\n",i,j,data->tokens[i][j]);

		if (check_error(data, data->tokens) == -1)
			handle_error(data);
		else
		{
			// FREE COMMAND
			free(data->command);
			//
			// // PARSER
			data->parser = ft_parser(data, data->tokens);
			//
			// FREE LEXER
				i = 0;
				while (data->tokens[i])
				{
					free_tab_str(data->tokens[i]);
					i++;
				}
				free(data->tokens);
		// 	//
		// 	// // EXECUTOR
		// 	// ast_exec(data);
		// 	//
		// 	// // FREE PARSER
		// 	// free_ast(data->parser);
		}
	}
}
