#include "../include/minishell.h"

t_redir	**set_redirections(char *command)
{
	char	**tokens;
	int		i;
	char	*str;
	int		fd;
	int		saved_fd;
	t_redir	**redirections;

	tokens = ft_split(command, '>');
	i = 0;
	while (tokens[i])
		i++;
	if (!(redirections = malloc((i + 1) * sizeof(t_redir *))))
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		redirections[i] = malloc(sizeof(t_redir));
		if (i == 0)
			redirections[i]->saved_fd = dup(1);
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

void	reset_redirections(t_redir **redirections)
{
	int		i;

	i = 0;
	printf("%d\n", redirections[0]->saved_fd);
	dup2(redirections[0]->saved_fd, 1);
	close(redirections[0]->saved_fd);
	while (redirections[i])
	{
		free(redirections[i]->str);
		free(redirections[i]);
		i++;
	}
	free(redirections);
}
