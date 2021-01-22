/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:02:54 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/17 15:02:56 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
int		ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
}

int		ft_search(char c, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return(1);
		i++;
	}
	return(0);
}

int		ft_indexof(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_redirection	**set_redirections(char *command)
{
	char	**tokens;
	int		i;
	char	*str;
	int		fd;
	int		saved_stdout;
	t_redirection	**redirections;

	tokens = ft_split(command, '>');
	i = 0;
	while (tokens[i])
		i++;
	if (!(redirections = malloc((i + 1) * sizeof(t_redirection *))))
		return (NULL);
	// printf("%s | %s\n", tokens[0], tokens[1]);
	i = 0;
	while (tokens[i])
	{
		redirections[i] = malloc(sizeof(t_redirection));
		if (i == 0) redirections[i]->saved_stdout = dup(1);
		redirections[i]->str = ft_strtrim(tokens[i], " ");
		printf("redirections[%d] = %s\n", i, redirections[i]->str);
		redirections[i]->type = (i == 0) ? NONE : REDIRECT_STDOUT;

		if (redirections[i]->type == REDIRECT_STDOUT)
		{
			fd = open(str, O_WRONLY | O_CREAT, 0777);
			dup2(fd, 1);
		}
		close(fd);
		i++;
	}
	redirections[i] = NULL;
	free_tab_str(tokens);
	return (redirections);
}

void	reset_redirections(t_redirection **redirections)
{
	int		i;

	i = 0;
	printf("%d\n", redirections[0]->saved_stdout);

	dup2(redirections[0]->saved_stdout, 1);
	close(redirections[0]->saved_stdout);

	while (redirections[i])
	{
		free(redirections[i]->str);
		free(redirections[i]);
		i++;
	}
	free(redirections);
}

int		tab_str_len(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
