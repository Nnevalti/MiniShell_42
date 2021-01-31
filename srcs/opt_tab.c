#include "../include/minishell.h"

int		get_nb_opt(char *opt)
{
	int i;
	int nb_opt;

	i = 0;
	nb_opt = 1;
	while(opt[i])
	{
		if (opt[i] == '\"')
		{
			i++;
			while(opt[i] != '\"')
			{
				if (opt[i] == '\\')
					i += 2;
				else
					i++;
			}
			i++;
		}
		else if (opt[i] == '\'')
		{
			i++;
			while(opt[i] != '\'')
				i++;
			i++;
		}
		else if (opt[i] == '\\')
			i+= 2;
		else if (ft_isblank(opt[i]))
		{
			i++;
			while(ft_isblank(opt[i]))
				i++;
			nb_opt++;
		}
		else
			i++;
	}
	return(nb_opt);
}
void	get_opt_tab(t_command *current, char *opt, int nb_opt)
{
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	start = 0;
	if (!(current->opt_tab = malloc(sizeof(char *) *(nb_opt + 1))))
		return ;
	while(opt[i])
	{
		if (opt[i] == '\"')
		{
			i++;
			while(opt[i] != '\"')
			{
				if (opt[i] == '\\')
					i += 2;
				else
					i++;
			}
			i++;
		}
		else if (opt[i] == '\'')
		{
			i++;
			while(opt[i] != '\'')
				i++;
			i++;
		}
		else if (opt[i] == '\\')
			i+= 2;
		else if (ft_isblank(opt[i]))
		{
			current->opt_tab[j] = ft_substr(opt, start, i - start);
			j++;
			i++;
			while(ft_isblank(opt[i]))
				i++;
			start = i;
		}
		else
			i++;
	}
	current->opt_tab[j] = ft_substr(opt, start, i - start);
	j++;
	current->opt_tab[j] = NULL;
	return ;
}
void	create_opt_tab(t_command *current, t_data *data)
{
	int nb_opt;

	if (current->opt)
	{
		nb_opt = get_nb_opt(current->opt);
		get_opt_tab(current, current->opt, nb_opt);
	}
	return ;
}
