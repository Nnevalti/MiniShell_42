#include "../include/minishell.h"

t_tree	*ft_init_struct(void)
{
	t_tree	*test;

	if (!(test = (t_tree *)malloc(sizeof(t_tree))))
		return(NULL);
	test->type = DEFAULT;
	test->command = NULL;
	test->options = NULL;
	test->file = NULL;
	test->left = NULL;
	test->right = NULL;

	return(test);
}

char		**ft_substr_array_left(char **array, int index)
{
	int		i;
	char	**new_array;

	if (!(new_array = malloc(sizeof(char *) * index)))
		return(NULL);
	i = 0;
	while (i < index)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
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
	if (!(new_array = malloc(sizeof(char *) * len)))
		return(NULL);
	i = 0;
	while (array[index + 1 + i])
	{
		new_array[i] = ft_strdup(array[index + 1 + i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

int	ft_priority(char **commands, t_type *priotype)
{
	int i;
	int priority;

	i = 0;
	priority = 0;
	while(commands[i])
	{
		printf("token %d: %s\n",i,commands[i]);
		if (!ft_strcmp(commands[i], ";"))
		{
			priority = i;
			*priotype = SEMI_COLON;
		}
		// else if (!ft_strcmp(commands[i], "&&") && *priotype >= AND)
		// {
		// 	priority = i;
		// 	*priotype = AND;
		// }
		else if (!ft_strcmp(commands[i], "|") && *priotype >= PIPE && (i <= priority
	|| *priotype == COMMAND))
		{
			priority = i;
			*priotype = PIPE;
		}
		else if (!ft_strcmp(commands[i], ">") && *priotype >= PIPE && (i <= priority
	|| *priotype == COMMAND))
		{
			priority = i;
			*priotype = REDIR_STDOUT;
		}
		else if (!ft_strcmp(commands[i], ">>") && *priotype >= PIPE && (i <= priority
	|| *priotype == COMMAND))
		{
			priority = i;
			*priotype = APP_STDOUT;
		}
		else if (!ft_strcmp(commands[i], "<") && *priotype >= PIPE && (i <= priority
	|| *priotype == COMMAND))
		{
			priority = i;
			*priotype = REDIR_STDIN;
		}
		else if ( *priotype >= COMMAND)
		{
			priority = 0;
			*priotype = COMMAND;
		}
		i++;
	}
	return(priority);
}
t_tree	*ft_parser(char **commands)
{
	int i;
	int priority;
	t_type priotype;
	t_tree	*test;
	char **left;
	char **right;

	priotype = DEFAULT;
	test = ft_init_struct();
	priority = ft_priority(commands,&priotype);
	printf("priority %d | priotype: %d | priocommand: %s\n",priority,
		priotype,commands[priority]);

	test->type = priotype;
	if (priotype == COMMAND)
	{
		test->command  = ft_strdup(commands[priority]);
		if (commands[priority + 1])
			test->options = ft_substr_array_right(commands, priority);
	}
	else if (priotype == REDIR_STDOUT || priotype == APP_STDOUT
		|| priotype == REDIR_STDIN)
	{
		printf("REDIR\n");
		left = ft_substr_array_left(commands, priority);
		test->file = ft_strdup(commands[priority + 1]);
		if (commands[priority + 2])
			right = ft_substr_array_right(commands, priority + 1);
		else
			right = NULL;
	}
	else
	{
		printf("tamereelse\n");
		if (priority)
			left = ft_substr_array_left(commands, priority);
		right = ft_substr_array_right(commands, priority);
	}
	i = 0;
	// while(priority && left[i])
	// {
	// 	printf("leeft %d: %s\n",i,left[i]);
	// 	i++;
	// }
	// i = 0;
	// while(right[i])
	// {
	// 	printf("riight %d: %s\n",i,right[i]);
	// 	i++;
	// }

	if (!(test->type == COMMAND))
	{
		if (priority)
			test->left = ft_parser(left);
		// printf("pointeur %d\n", test->left->type);
		if (right)
			test->right = ft_parser(right);
	}

	while(test->type == COMMAND && test->options[i])
	{
		printf("opt %d: %s\n",i,test->options[i]);
		i++;
	}

	if (!(test->type == COMMAND))
	{
		free_tab_str(left);
		if (!(test->type >= REDIR_STDOUT))
			free_tab_str(right);
	}
	return(test);
}
