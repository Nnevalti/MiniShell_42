#include "../include/minishell.h"

t_tree	*set_struct(t_tree *test, t_type type, char *command, char **options, void *left, void *right)
{
	test->type = type;
	test->command = command;
	test->options = options;
	test->left = left;
	test->right = right;

	return(test);
}

void	analyze_struct(t_tree *ptr)
{
	if (ptr->type == PIPE)
	{
		printf("ouverture du chemin de disucssion entre left et right\n");
	}
	if (ptr->type == COMMAND)
	{
		printf("execve de la commande\n");
	}
	if (ptr->type == REDIR)
	{
		if (ptr->redir_type == REDIRECT_STDOUT)
			printf("REDIR_STDOUT: %s\n", ptr->file);
		else if (ptr->redir_type == APPEND_STDOUT)
			printf("APP_STDOUT: %s\n", ptr->file);
		else if (ptr->redir_type == REDIRECT_STDIN)
			printf("REDIR_STDIN: %s\n", ptr->file);
	}
	return ;
}

void	analyze_end_struct(t_tree *ptr)
{
	if (ptr->type == PIPE)
	{
		printf("fermeture du chemin de disucssion entre left et right\n");
	}
	if (ptr->type == REDIR)
	{
		if (ptr->redir_type == REDIRECT_STDOUT)
			printf("REDIR_STDOUT close\n");
		else if (ptr->redir_type == APPEND_STDOUT)
			printf("APP_STDOUT close\n");
		else if (ptr->redir_type == REDIRECT_STDIN)
			printf("REDIR_STDIN close\n");
	}
	return ;
}

void recursive(t_tree *ptr)
{
	int		i;

	i = 0;
	printf("%d %s ", ptr->type, ptr->command);
	if (ptr->options != NULL)
	{
		while (ptr->options[i])
		{
			printf("%s ", ptr->options[i]);
			i++;
		}
	}
	printf("\n");
	// start
	analyze_struct(ptr);
	if (ptr->left != NULL)
	{
		recursive(ptr->left);
		if (ptr->right != NULL)
		{
			recursive(ptr->right);
			analyze_end_struct(ptr);
		}
	}
	else if (ptr->right != NULL)
		printf("WTF error\n");

	return ;
}

void ast_exec(t_tree *entry) // devra prendre un t_tree *entry en paramètre
{
	printf("\nIN AST_EXEC\n");
	recursive(entry); // deviendra ast_exec par la suite
	printf("WE LEAVE AST_EXEC\n\n");
}
