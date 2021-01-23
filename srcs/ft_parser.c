#include "../include/minishell.h"

t_command	*ft_init_struct(void)
{
	t_command	*ptr;

	if (!(ptr = (t_command *)malloc(sizeof(t_command))))
		return(NULL);
	ptr->cmd = NULL;
	ptr->opt = NULL;
	ptr->redir = NULL;
	ptr->pipe = NULL;
	ptr->next = NULL;
	ptr->previous = NULL;

	return(ptr);
}

t_command	*ft_create_struct(char *tokens)
{
	t_command	*ptr;
	int i;

	i = 0;
	ptr = ft_init_struct();
	while(tokens[i])
	{
		if (ft_isblank(tokens[i]))
		{
			ptr->cmd = ft_substr(tokens,0,i);
			printf("ptr->cmd : %s\n",ptr->cmd);
			while(ft_isblank(tokens[i]))
				i++;
			if (tokens[i] == '\0')
				return(ptr);
			else
			{
				ptr->opt = ft_substr(tokens, i, ft_strlen(&tokens[i]));
				printf("ptr->opt : %s\n",ptr->opt);

				return(ptr);
			}
		}
		i++;
	}
	ptr->cmd = ft_substr(tokens,0,i);
	return(ptr);

}

int		multiple_commands(char **tokens)
{
	int i;

	i = 0;
	while(tokens[i])
		i++;
	if ( i > 1)
		return(1);
	return(0);
}

t_command	*ft_parser(t_data *data)
{
	t_command	**entry;
	int i;

	if (!(entry = malloc(sizeof(t_command *) * data->nb_cmds + 1)))
		return(NULL);

//boucler sur les redirs
//trouver un pipe
//
	i = 0;
	while(data->tokens[i])
	{
		entry[i] = ft_create_struct(data->tokens[i][0]);
		if (multiple_commands(data->tokens[i])) //verifier si plusieurs commands dans tokens[i]
		{
			printf("YES MULTIPLE commands\n");
			// parse_commands(data->tokens[i]);
		}
		else
		{
			printf("NO MULTIPLE commands\n");
			// entry = ft_init_struct();
			//substr command in entry->command
			//substr opt in entry->opt
		}
		i++;
	}
	entry[i] = NULL;
	return(NULL);
}
