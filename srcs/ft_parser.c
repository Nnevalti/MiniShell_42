#include "../include/minishell.h"

t_struct *ft_init_struct(char *command)
{
	t_struct	*structure;

	structure = malloc(sizeof(t_struct));
	return(structure);
}
void	ft_priority(t_type *test)
{
	printf("bonjour\n");
	*test = SEMI_COLON;
	printf("bonjour\n");
	printf("in ft %d\n",*test);
	printf("bonjour\n");


}
int	ft_parser(char **commands)
{
	int i;
	int priority;
	t_type priotype;
	t_type testeuh;
	t_struct	*test;

	i = 0;
	priority = 0;
	priotype = DEFAULT;
	while(commands[i])
	{
		printf("commande %d: %s\n",i,commands[i]);
		if (!ft_strcmp(commands[i], ";"))
		{
			priority = i;
			priotype = SEMI_COLON;
		}
		if (!ft_strcmp(commands[i], "&&") && priotype >= AND)
		{
			priority = i;
			priotype = AND;
		}
		if (!ft_strcmp(commands[i], "|") && priotype >= PIPE)
		{
			priority = i;
			priotype = PIPE;
		}

		i++;
	}
	printf("priority %d and i %d\n",priority,i);
	printf("priotype : %d\n", priotype);
	test = ft_init_struct(commands[priority]);
	test->type=priotype;
	printf("ICI %d\n",test->type);

	ft_priority(&testeuh);
	printf("la %d\n",testeuh);
}
