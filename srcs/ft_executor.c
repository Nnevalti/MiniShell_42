#include "../include/minishell.h"

// void	run_exec(char *command, char **argv, char **env, , int index)

// void	handle_pipe(t_command *current)
// {
// 	if(current->pipe)
// 		pipe(fd);
// }

char	**prepend_str(char *str, char **array_str)
{
	int		i;
	int		j;
	char	**new_array;

	i = tab_str_len(array_str);
	if (!(new_array = malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	new_array[0] = ft_strdup(str);
	i = 1;
	j = 0;
	while (array_str[j])
	{
		new_array[i] = ft_strdup(array_str[j]);
		i++;
		j++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	analyse_parser(t_command *cmd, t_data *data)
{
	t_command	*current;
	char		*path;
	char	**tmp;

	current = cmd;
	while (current)
	{
		handle_env(current, data);
		create_opt_tab(current, data);
		handle_bsq(current, data);
		if (current->opt_tab)
		{
			tmp = prepend_str(current->cmd, current->opt_tab);
			free_tab_str(current->opt_tab);
			current->opt_tab = tmp;
		}
		else
		{
			if (!(current->opt_tab = malloc(sizeof(char *) * 2)))
				return ;
			current->opt_tab[0] = ft_strdup(current->cmd);
			current->opt_tab[1] = NULL;
		}
		if (current->redir)
			handle_redir(data, current, current->redir);
		if (current->pipe)
			handle_pipes(data, current, current->pipe);
		if (data->error->errtype == NOERROR)
		{
			exec_cmd(data, current);
			if (current->redir)
				reset_redir(current->last_stdin, current->last_stdout);
		}
		else
		{
			handle_error(data);
			return ;
		}
		current = current->next;
	}
	return ;
}

void	ft_executor(t_data *data)
{
	int i;

	i = 0;
	while (data->parser[i])
	{
		analyse_parser(data->parser[i], data);
		i++;
	}
}
