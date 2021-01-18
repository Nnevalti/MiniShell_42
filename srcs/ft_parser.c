#include "../include/minishell.h"

t_tree	*ft_init_struct(void)
{
	t_tree	*tree;

	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		return(NULL);
	tree->type = DEFAULT;
	tree->command = NULL;
	tree->options = NULL;
	tree->redir_type = NONE;
	tree->file = NULL;
	tree->left = NULL;
	tree->right = NULL;

	return(tree);
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

int	ft_priority(char **tokens, t_tree *tree)
{
	int i;
	int priority;

	i = 0;
	priority = 0;
	while(tokens[i])
	{
		if (!ft_strcmp(tokens[i], ";"))
		{
			priority = i;
			tree->type = SEMI_COLON;
		}
		else if (!ft_strcmp(tokens[i], "|") && tree->type >= PIPE)
		{
			priority = i;
			tree->type = PIPE;
		}
		else if (!ft_strcmp(tokens[i], ">") && tree->type >= REDIR)
		{
			priority = i;
			tree->type = REDIR;
			tree->redir_type = REDIRECT_STDOUT;

		}
		else if (!ft_strcmp(tokens[i], ">>") && tree->type >= REDIR)
		{
			priority = i;
			tree->type = REDIR;
			tree->redir_type = APPEND_STDOUT;

		}
		else if (!ft_strcmp(tokens[i], "<") && tree->type >= REDIR)
		{
			priority = i;
			tree->type = REDIR;
			tree->redir_type = REDIRECT_STDIN;

		}
		else if ( tree->type >= COMMAND)
		{
			priority = 0;
			tree->type = COMMAND;
		}
		i++;
	}
	return(priority);
}

t_tree		*ft_parser(char **tokens)
{
	int		i;
	int		priority;
	t_tree	*tree;
	char	**left;
	char	**right;

	tree = ft_init_struct();
	priority = ft_priority(tokens, tree); // rename priority : define type ?

	printf("Priority case: %d | Value: %s | Type: %d \n",priority,
		tokens[priority], tree->type);

	if(tree->type == SEMI_COLON || tree->type == PIPE)
	{
		left = ft_substr_array_left(tokens, priority);
		right = ft_substr_array_right(tokens, priority);
	}
	else if (tree->type == REDIR)
	{
		if (tree->redir_type == REDIRECT_STDOUT
			|| tree->redir_type == APPEND_STDOUT)
		{
			left = ft_substr_array_left(tokens, priority);
			right = NULL;
			tree->file = ft_strdup(tokens[priority + 1]);
		}
		else if (tree->redir_type == REDIRECT_STDIN)
		{
			right = ft_substr_array_right(tokens, priority);
			left = NULL;
			tree->file = ft_strdup(tokens[priority + 1]);
		}
	}
	else if (tree->type == COMMAND)
	{
		left = NULL;
		right = NULL;
		tree->command  = ft_strdup(tokens[priority]);
		if (tokens[priority + 1] != NULL)
			tree->options = ft_substr_array_right(tokens, priority);
	}
	if (left != NULL)
	{
		i = 0;
		while(priority && left[i])
		{
			printf("Left %d: %s\n",i,left[i]);
			i++;
		}
		if (right != NULL)
		{
			i = 0;
			while(right[i])
			{
				printf("Right %d: %s\n",i,right[i]);
				i++;
			}
		}
	}

	if (tree->type == COMMAND && tree->options)
	{
		i = 0;
		printf("I'm here ! %s \n", tree->command);
		while(tree->options[i])
		{
			printf("opt %d: %s\n",i,tree->options[i]);
			i++;
		}
	}

	if (left != NULL)
	{
		tree->left = ft_parser(left);
		free_tab_str(left);
		if (right != NULL)
		{
			tree->right = ft_parser(right);
			free_tab_str(right);
		}
	}
	return(tree);
}
