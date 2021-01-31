//
// int		handle_backslash(char *str, char **tmp, char **new_str, int start)
// {
// 	// int		i;
// 	//
// 	// i = 0;
//
//
// }

#include "../include/minishell.h"

char	*trim_bsq(char *str)
{
	int		i;
	int		start;
	char	*new_str;
	char	*tmp;

	i = 0;
	start = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (!new_str)
				new_str = ft_substr(str, start, i);
			else
			{
				tmp = ft_strnjoin(new_str, &str[start], i - start);
				free(new_str);
				new_str = tmp;
			}
			i++;
			start = i;
			i++;
		}
		else if (str[i] == '\"')
		{
			if (!new_str)
				new_str = ft_substr(str, start, i);
			else
			{
				tmp = ft_strnjoin(new_str, &str[start], i - start);
				free(new_str);
				new_str = tmp;
			}
			i++;
			start = i;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == '\\')
				{
					if (ft_search(str[i + 1], "\\$\""))
					{
						if (!new_str)
							new_str = ft_substr(str, start, i);
						else
						{
							tmp = ft_strnjoin(new_str, &str[start], i - start);
							free(new_str);
							new_str = tmp;
						}
						i++;
						start = i;
						i++;
					}
					else
						i += 2;
				}
				else
					i++;
			}
			if (!new_str)
				new_str = ft_substr(str, start, i - start);
			else
			{
				tmp = ft_strnjoin(new_str, &str[start], i - start);
				free(new_str);
				new_str = tmp;
			}
			i++;
			start = i;
		}
		else if (str[i] == '\'')
		{
			if (!new_str)
				new_str = ft_substr(str, start, i);
			else
			{
				tmp = ft_strnjoin(new_str, &str[start], i - start);
				free(new_str);
				new_str = tmp;
			}
			i++;
			start = i;
			while (str[i] != '\'')
				i++;
			if (!new_str)
				new_str = ft_substr(str, start, i);
			else
			{
				tmp = ft_strnjoin(new_str, &str[start], i - start);
				free(new_str);
				new_str = tmp;
			}
			i++;
			start = i;
		}
		else
			i++;
	}
	if (!new_str)
	{
		new_str = ft_substr(str, start, i);
	}
	else
	{
		tmp = ft_strnjoin(new_str, &str[start], i - start);
		free(new_str);
		new_str = tmp;
	}
	return (new_str);
}

void	handle_bsq(t_command *current, t_data *data)
{
	char *tmp;
	t_redir *redir;
	int i;

	i = 0;
	// tmp = trim_bsq(current->cmd);
	// free(current->cmd);
	// current->cmd = tmp;
	if (current->opt_tab)
	{
		while(current->opt_tab[i])
		{
			printf(" wld opt_tab[%d] = [%s]\n",i,current->opt_tab[i]);
			tmp = trim_bsq(current->opt_tab[i]);
			free(current->opt_tab[i]);
			current->opt_tab[i] = tmp;
			printf(" mew opt_tab[%d] = [%s]\n",i,current->opt_tab[i]);
			i++;
		}
	}
	// if (current->redir)
	// {
	// 	redir = current->redir;
	// 	while (redir)
	// 	{
	// 		redir->str = trim_bsq(redir->str);
	// 		redir = redir->next;
	// 	}
	// }
	return ;
}
