#include "../include/minishell.h"

t_tree	*ft_init_tree(void)
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


// int			get_cmd(t_tree *entry, char *tokens, int j)
// {
// 	while (!(ft_isblank(tokens[j])))
// 		j++;
// 	entry->command = ft_substr(tokens, 0, j);
// 	while (ft_isblank(tokens[j]))
// 		j++;
// 	entry->options = ft_substr(tokens, j, ft_strlen(&tokens[j]));
// 	return (j);
// }>

t_tree		*parse_tokens(t_data *data, char **tokens)
{
	int		i;
	int		j;
	int		priority;
	t_tree	*entry;


	i = 0;
	entry = ft_init_tree();
}

t_tree		**ft_parser(t_data *data, char ***tokens)
{
	int		i;
	t_tree	**trees;

	if (!(trees = malloc(sizeof(t_tree *) * data->nb_cmds + 1)))
		return (NULL);
	i = 0;
	while (tokens && tokens[i])
	{
		trees[i] = parse_tokens(data, tokens[i]);
		i++;
	}
	trees[i] = NULL;
	return(NULL);
}
