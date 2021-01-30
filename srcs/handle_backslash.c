#include "../include/minishell.h"

char	*trim_bs(char *str, t_data *data)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;
	char	*new_str;

	i = 0;
	start = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (!new_str)
				new_str = ft_substr(str, start, i - 1)
			else
			{
				tmp = ft_substr(str, start, i - 1);
			}
			i++;
			start = i;
			if (str[i] == '\\')
				i++;
		}
		i++;
	}
	return (new_str);
}

void		handle_backslash(t_command *current, t_data *data)
{
	char	*tmp;
	t_redir	*redir_tmp;

	tmp = trim_bs(current->cmd, data);
	free(current->cmd);
	current->cmd = tmp;
	if (current->opt)
	{
		tmp = trim_bs(current->opt, data);
		free(current->opt);
		current->opt = tmp;
	}
	redir_tmp = current->redir;
	while (redir_tmp)
	{
		tmp = trim_bs(redir_tmp->str, data);
		free(redir_tmp->str);
		redir_tmp->str = tmp;
		redir_tmp = redir_tmp->next;
	}
	return ;
}
