#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>


//ls - l | sort | cat -e

/*
** pipex.c - multipipes support
*/

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/*
 * loop over commands by sharing
 * pipes.
 */
static void pipeline(char ***cmd)
{
	int fd[2];
	int pid;
	int fdd = 0;				/* Backup */

	while (*cmd != NULL)
	{
		pipe(fd);				/* Sharing bidiflow */
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0) //fork renvoie 0 -> on est donc dans l'enfant
		{
			dup2(fdd, 0);
			if (*(cmd + 1) != NULL)
			{
				dup2(fd[1], 1);
			}
			close(fd[0]);
			execvp((*cmd)[0], *cmd);
			exit(1);
		}
		else // fork renvoie 1 -> on est dans le parent
		{
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
			cmd++;
		}
	}
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int	main(void)
{
	int test;
	struct stat buffer;
	// char **env;
 	// int stat(const char *pathname, struct stat *statbuf);
	if (!(test = stat("/bin/cat", &buffer)))
		printf("FILE EXIST\n");
	else
		printf("FILE DOES NOT EXIST\n");
	// char *const argv[] = {"/usr/bin/echo","salut",NULL};;
	// char *ls[] = {"echo", "test", NULL};
	// char *sort[] = {"sort", NULL};
	// char *cat[] = {"cat", "-e", NULL};
	// char **cmd[] = {ls, sort, cat, NULL};

	// pipeline(cmd);
	// if (execve(argv[0],argv,NULL)==-1)
	// 	perror("excve");
	return (0);
}

// void main(void)
// {
// 	int nb_pipes = 2;
// 	int i = 0;
//
// 	int pipes[2 * nb_pipes];
// 	while(i < nb_pipes)
// 	{
// 		pipe(pipes + (2 * i));
// 		i++;
// 	}
//
// }

// void main(void)
// {
// 	int nb_pipes = 2;
//
// 	int *pipes[2];
//
// 	if(!(pipes = malloc(sizeof(int) * nb_pipes + 1)))
// 		return;
//
// 	char *ls_args[] = {"ls", "-l", NULL};
//     char *sort_args[] = {"sort", NULL};
// 	char *cat_args[] = {"cat", "-e", NULL};
//
// 	pipe(pipefd);
//
// 	if ((pid = fork()) == -1)
// 		return;
// 	if (pid == 0) //enfant
// 	{
// 		dup2(pipefd[0],0);
// 		close(pipefd[1]);
// 		execvp("sort", sort_args);
// 		// exit(0);
// 	}
// 	else //parent
// 	{
// 		dup2(pipefd[1],1);
// 		close(pipefd[0]);
// 		execvp("ls", ls_args);
// 	}
// 	// return;
// }
