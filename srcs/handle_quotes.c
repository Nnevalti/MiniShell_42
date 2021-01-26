#include "../include/minishell.h"

int		get_nb_opt(char *opt)
{
	int i;
	int nb_opt;

	i = 0;
	nb_opt = 1;
	while (ft_isblank(opt[i]))
		i++;
	while(opt[i])
	{
		if (opt[i] == '\'')
		{
			i++;
			while(opt[i] && opt[i] != '\'')
				i++;
			i++;
		}
		else if (opt[i] == '\"')
		{
			i++;
			while(opt[i] && opt[i] != '\"')
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
			while(ft_isblank(opt[i]))
				i++;
			nb_opt++;
		}
		else if(opt[i])
			i++;
	}
	return(nb_opt);
}

char	**get_opt_tab(char *opt, t_data *data, int nb_opt)
{
	int i;
	int j;
	int start;
	int len;
	char **opt_tab;
	char *tmp;

	tmp = NULL;
	if (!(opt_tab = malloc(sizeof(char *) * (nb_opt + 1))))
		return(NULL);
	i = 0;
	j = 0;
	start = 0;
	while (ft_isblank(opt[i]))
		i++;
	while(opt[i])
	{
		if (opt[i] == '\'')
		{
			i++;
			start = i;
			while(opt[i] && opt[i] != '\'')
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
			while(opt[i] && opt[i] != '\"')
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
			while(ft_isblank(opt[i]))
				i++;
			tmp = NULL;
			j++;
		}
		else if(opt[i])
		{
			start = i;
			while (opt[i] && opt[i] != '\'' && opt[i] != '\"' && !ft_isblank(opt[i]))
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
	return(opt_tab);
}

void	handle_quotes(t_command *current, t_data *data)
{
	int i;
	int nb_opt;

	i = 0;
	nb_opt = 0;
	if (current->opt && ft_strcmp(current->opt,"\0"))
		nb_opt = get_nb_opt(current->opt);
	printf("nb_opt %d\n",nb_opt);
	if (current->opt && ft_strcmp(current->opt,"\0"))
		current->opt_tab = get_opt_tab(current->opt, data, nb_opt);
	if (current->opt && ft_strcmp(current->opt,"\0"))
	{
		for (int j = 0; current->opt_tab[j]; j++)
			printf("opt_tab : [%s]\n", current->opt_tab[j]);
	}
	return;
}
