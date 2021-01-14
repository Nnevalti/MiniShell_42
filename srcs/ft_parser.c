#include "../include/minishell.h"

int ft_length(char *str)
{
	int i;
	i = 0;
	while(str[i])
		i++;
	return(i);
}

t_struct *ft_init_struct(char *command)
{
	t_struct	*structure;

	structure = malloc(sizeof(t_struct));
	return(structure);
}
int	ft_priority(char **commands, t_type *priotype)
{
	int i;
	int priority;
	printf("ft priotype : %d\n", *priotype);
	i = 0;
	priority = 0;
	while(commands[i])
	{
		printf("commande %d: %s\n",i,commands[i]);
		if (!ft_strcmp(commands[i], ";"))
		{
			priority = i;
			*priotype = SEMI_COLON;
		}
		if (!ft_strcmp(commands[i], "&&") && *priotype >= AND)
		{
			priority = i;
			*priotype = AND;
		}
		if (!ft_strcmp(commands[i], "|") && *priotype >= PIPE)
		{
			priority = i;
			*priotype = PIPE;
		}
		i++;
	}
	return(priority);
}
void	*ft_parser(char **commands)
{
	int i;
	int priority;
	t_type priotype;
	t_struct	*test;
	char **left;

	priotype = DEFAULT;
	priority = ft_priority(commands,&priotype);
	printf("priority %d\n",priority);
	printf("priotype : %d\n", priotype);
	printf("priocommand: %s\n",commands[priority]);

	test = ft_init_struct(commands[priority]);
	test->type = priotype;
	if (priotype == COMMAND)
		test->command  = commands[priority];
	else
		test->command = NULL;

	if (!(left = (char **)malloc((priority + 1) * sizeof(char *))))
		return(NULL);
	i = 0;
	while(i < priority)
	{
		left[i] = ft_substr(commands[i],0, ft_length(commands[i]));
		i++;
	}
	i = 0;
	while(left[i] && priority)
	{
		printf("leeft %d: %s\n",i,left[i]);
		i++;
	}
	// printf("wut priority %d\n",priority);
	if (priority != 0)
	{
		test->left = ft_parser(left);
		// printf("pointeur %d\n", test->left->type);

	}

	return(test);
}
