#include "../include/minishell.h"

t_struct	*init_struct(void)
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

t_struct	*set_struct(t_struct *test, t_type type, char *command, char **options, void *left, void *right)
{
	test->type = type;
	test->command = command;
	test->options = options;
	test->left = left;
	test->right = right;

	return(test);
}

t_struct 	*test(void) {
	t_struct	*entry = init_struct();
	t_struct	*pipe = init_struct();
	t_struct	*command_ls2 = init_struct();
	t_struct	*command_ls = init_struct();
	t_struct	*command_sort = init_struct();

	char **options_ls;
	options_ls = malloc(sizeof(char **) * 2);
	*options_ls = malloc(sizeof(char*) * 3);
	options_ls[0] = "-l";
	options_ls[1] = "\0";

	entry = set_struct(entry, AND, NULL, NULL, pipe, command_ls2);
	pipe = set_struct(pipe, PIPE, NULL, NULL, command_ls, command_sort);
	command_ls2 = set_struct(command_ls2, COMMAND, "ls", NULL, NULL, NULL);
	command_ls = set_struct(command_ls, COMMAND, "ls", options_ls, NULL, NULL);
	command_sort = set_struct(command_sort, COMMAND, "sort", NULL, NULL, NULL);

	return (entry);
}

void	analyze_struct(t_struct *ptr)
{
	if (ptr->type == PIPE)
	{
		printf("ouverture du chemin de disucssion entre left et rigth\n");
	}
	if (ptr->type == COMMAND)
	{
		printf("execve de la commande\n");
	}
	if (ptr->type == REDIR_STDOUT)
	{
		printf("REDIR_STDOUT\n");
	}
	if (ptr->type == APP_STDOUT)
	{
		printf("APP_STDOUT\n");
	}
	if (ptr->type == REDIR_STDIN)
	{
		printf("REDIR_STDIN\n");
	}
	return ;
}

void	analyze_end_struct(t_struct *ptr)
{
	if (ptr->type == PIPE)
	{
		printf("fermeture du chemin de disucssion entre left et rigth\n");
	}
	if (ptr->type == REDIR_STDOUT)
	{
		printf("REDIR_STDOUT close\n");
	}
	if (ptr->type == APP_STDOUT)
	{
		printf("APP_STDOUT close\n");
	}
	if (ptr->type == REDIR_STDIN)
	{
		printf("REDIR_STDIN close\n");
	}
	return ;
}

void recursive(t_struct *ptr)
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

void ast_exec(void)
{
	t_struct *entry;

	printf("\nIN AST_EXEC\n");
	entry = test();
	recursive(entry);
	printf("WE LEAVE AST_EXEC\n\n");
}
