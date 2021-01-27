#include "../include/minishell.h"

int		get_nb_opt(char *opt)
{
	int i;
	int nb_opt;

	i = 0;
	nb_opt = 1;
	while (ft_isblank(opt[i]))
		i++;
	while (opt[i])
	{
		if (opt[i] == '\'')
		{
			i++;
			while (opt[i] && opt[i] != '\'')
				i++;
			i++;
		}
		else if (opt[i] == '\"')
		{
			i++;
			while (opt[i] && opt[i] != '\"')
			{
				if (opt[i] == '\\')
					i += 2;
				else
					i++;
			}
			i++;
		}
		else if (ft_isblank(opt[i]))
		{
			while (ft_isblank(opt[i]))
				i++;
			nb_opt++;
		}
		else if (opt[i])
			i++;
	}
	return (nb_opt);
}

char	**get_opt_tab(char *opt, t_data *data, int nb_opt)
{
	int		i;
	int		j;
	int		start;
	int		len;
	char	**opt_tab;
	char	*tmp;

	tmp = NULL;
	if (!(opt_tab = malloc(sizeof(char *) * (nb_opt + 1))))
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (ft_isblank(opt[i]))
		i++;
	while (opt[i])
	{
		if (opt[i] == '\'')
		{
			i++;
			start = i;
			while (opt[i] && opt[i] != '\'')
				i++;
			len = i - start;
			if (!tmp || !*tmp)
			{
				tmp = ft_substr(opt, start, len);
				opt_tab[j] = tmp;
			}
			else
			{
				tmp = ft_strnjoin(tmp, &opt[start], len);
				free(opt_tab[j]);
				opt_tab[j] = tmp;
			}
			i++;
		}
		else if (opt[i] == '\"')
		{
			i++;
			start = i;
			while (opt[i] && opt[i] != '\"')
			{
				if (opt[i] == '\\')
					i += 2;
				else
					i++;
			}
			len = i - start;
			if (!tmp || !*tmp)
			{
				tmp = ft_substr(opt, start, len);
				opt_tab[j] = tmp;
			}
			else
			{
				tmp = ft_strnjoin(tmp, &opt[start], len);
				free(opt_tab[j]);
				opt_tab[j] = tmp;
			}
			i++;
		}
		else if (ft_isblank(opt[i]))
		{
			while (ft_isblank(opt[i]))
				i++;
			tmp = NULL;
			j++;
		}
		else if (opt[i])
		{
			start = i;
			while (opt[i] && opt[i] != '\'' && opt[i] != '\"'
				&& !ft_isblank(opt[i]))
				i++;
			len = i - start;
			if (!tmp || !*tmp)
			{
				tmp = ft_substr(opt, start, len);
				opt_tab[j] = tmp;
			}
			else
			{
				tmp = ft_strnjoin(tmp, &opt[start], len);
				free(opt_tab[j]);
				opt_tab[j] = tmp;
			}
		}
	}
	j++;
	opt_tab[j] = NULL;
	return (opt_tab);
}

char	*handle_cmd_quotes(char *cmd, t_data *data)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	i = 0;
	start = 0;
	while (ft_isblank(cmd[i]))
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			start = i;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			len = i - start;
			if (!tmp || !*tmp)
			{
				tmp = ft_substr(cmd, start, len);
				tmp2 = tmp;
			}
			else
			{
				tmp = ft_strnjoin(tmp, &cmd[start], len);
				free(tmp2);
				tmp2 = tmp;
			}
			i++;
		}
		else if (cmd[i] == '\"')
		{
			i++;
			start = i;
			while (cmd[i] && cmd[i] != '\"')
			{
				if (cmd[i] == '\\')
					i += 2;
				else
					i++;
			}
			len = i - start;
			if (!tmp || !*tmp)
			{
				tmp = ft_substr(cmd, start, len);
				tmp2 = tmp;
			}
			else
			{
				tmp = ft_strnjoin(tmp, &cmd[start], len);
				free(tmp2);
				tmp2 = tmp;
			}
			i++;
		}
		else if (cmd[i])
		{
			start = i;
			while (cmd[i] && cmd[i] != '\'' && cmd[i] != '\"'
				&& !ft_isblank(cmd[i]))
				i++;
			len = i - start;
			if (!tmp || !*tmp)
			{
				tmp = ft_substr(cmd, start, len);
				tmp2 = tmp;
			}
			else
			{
				tmp = ft_strnjoin(tmp, &cmd[start], len);
				free(tmp2);
				tmp2 = tmp;
			}
		}
	}
	free(cmd);
	return (tmp2);
}

void	handle_quotes(t_command *current, t_data *data)
{
	int	i;
	int	nb_opt;
	t_redir *redir;

	i = 0;
	nb_opt = 0;
	if(current->cmd && ft_strcmp(current->cmd, "\0"))
		current->cmd = handle_cmd_quotes(current->cmd, data);
	if (current->opt && ft_strcmp(current->opt, "\0"))
		nb_opt = get_nb_opt(current->opt);
	if (current->opt && ft_strcmp(current->opt, "\0"))
		current->opt_tab = get_opt_tab(current->opt, data, nb_opt);
	if (current->redir)
	{
		redir = current->redir;
		while (redir)
		{
			redir->str = handle_cmd_quotes(redir->str, data);
			redir = redir->next;
		}
	}
	// HANDLE QUOTES FOR FILE NAME
	return ;
}
