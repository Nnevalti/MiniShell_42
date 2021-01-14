#include "../include/minishell.h"

t_struct	*ft_init_struct(void)
{
	t_struct	*test;

	test = malloc(sizeof(t_struct));
	test->type = DEFAULT;
	test->command = NULL;
	test->options = NULL;
	test->left = NULL;
	test->right = NULL;

	return(test);
}

char		**ft_substr_array_left(char **array, int index)
{
	int		i;
	char	**new_array;

	new_array = malloc(sizeof(char *) * index);
	i = 0;
	while (i > index)
	{
			new_array[i] = ft_strdup(array[i]);
			i++;
	}
	new_array[i] = "\0";
	return (new_array);
}

char		**ft_substr_array_right(char **array, int index)
{
	int		len;
	int		i;
	char	**new_array;

	len = 0;
	while (array[index + len])
		len++;
	new_array = malloc(sizeof(char *) * len + 1);
	i = 0;
	while (array[index + i])
	{
			new_array[i] = ft_strdup(array[index + i]);
			i++;
	}
	new_array[i] = "\0";
	return (new_array);
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
t_struct	*ft_parser(char **commands)
{
	int i;
	int priority;
	t_type priotype;
	t_struct	*test;
	char **left;
	char **right;

	priotype = DEFAULT;
	test = ft_init_struct();
	priority = ft_priority(commands,&priotype);
	printf("priority %d\n",priority);
	printf("priotype : %d\n", priotype);
	printf("priocommand: %s\n",commands[priority]);

	test->type = priotype;
	if (priotype == COMMAND)
	{
		test->command  = commands[priority];
	}

	if (!(left = (char **)malloc((priority + 1) * sizeof(char *))))
		return(NULL);
	i = 0;
	while(i < priority)
	{
		left[i] = ft_substr(commands[i],0, ft_strlen(commands[i]));
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
