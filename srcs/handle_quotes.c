#include "../include/minishell.h"

int		get_nb_opt(char *opt)
{
	int i;
	int nb_opt;

	i = 0;
	nb_opt = 1;
	printf("opt : [%s]\n",opt);
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

	if (!(opt_tab = malloc(sizeof(char *) * nb_opt + 1)))
		return(NULL);
	i = 0;
	j = 0;
	start = 0;
	tmp = NULL;
	while(opt[i])
	{
		if (opt[i] == '\'')
		{
			i++;
			start = i;
			while(opt[i] && opt[i] != '\'')
				i++;
			len = i - start - 1;
			if (tmp)
				opt_tab[j] = ft_strnjoin(tmp,&opt[start],len);
			else
				tmp = ft_substr(opt,start,len);
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
			j++;
			if(tmp)
				free(tmp);
		}
		else if(opt[i])
			i++;
	}
	return(opt_tab);
}

void	handle_quotes(t_command *current, t_data *data)
{
	int i;
	int nb_opt;

	i = 0;
	nb_opt = 0;
	if (current->opt)
		nb_opt = get_nb_opt(current->opt);
	printf("nb_pot %d\n",nb_opt);
	// if (!(current->opt_tab = malloc(sizeof(char *) * nb_opt + 1)))
	// 	return ;
	// current->opt_tab = get_opt_tab(current->opt, data, nb_opt);
	return;
}
