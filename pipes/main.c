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
// int	main(void)
// {
// 	int test;
// 	struct stat buffer;
// 	// char **env;
//  	// int stat(const char *pathname, struct stat *statbuf);
// 	if (!(test = stat("/bin/cat", &buffer)))
// 		printf("FILE EXIST\n");
// 	else
// 		printf("FILE DOES NOT EXIST\n");
// 	// char *const argv[] = {"/usr/bin/echo","salut",NULL};;
// 	// char *ls[] = {"echo", "test", NULL};
// 	// char *sort[] = {"sort", NULL};
// 	// char *cat[] = {"cat", "-e", NULL};
// 	// char **cmd[] = {ls, sort, cat, NULL};
//
// 	// pipeline(cmd);
// 	// if (execve(argv[0],argv,NULL)==-1)
// 	// 	perror("excve");
// 	return (0);
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

int main(int argc, char **argv)
{
  int pipefd[2];
  int pid;

  char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", "Villanova", NULL};

  // make a pipe (fds go in pipefd[0] and pipefd[1])

  pipe(pipefd);

  pid = fork();

  if (pid == 0)
    {
      // child gets here and handles "grep Villanova"

      // replace standard input with input part of pipe

      dup2(pipefd[0], 0);

      // close unused hald of pipe

      close(pipefd[1]);

      // execute grep

      execvp("grep", grep_args);
    }
  else
    {
      // parent gets here and handles "cat scores"

      // replace standard output with output part of pipe

      dup2(pipefd[1], 1);

      // close unused unput half of pipe

      close(pipefd[0]);

      // execute cat

      execvp("cat", cat_args);
    }
}
//
// int main(int argc, char **argv)
// {
//   int status;
//   int i;
//
//   // arguments for commands; your parser would be responsible for
//   // setting up arrays like these
//
//   char *cat_args[] = {"cat", "scores", NULL};
//   char *grep_args[] = {"grep", "Villanova", NULL};
//   char *cut_args[] = {"cut", "-b", "1-10", NULL};
//
//   // make 2 pipes (cat to grep and grep to cut); each has 2 fds
//
//   int pipes[4];
//   pipe(pipes); // sets up 1st pipe
//   pipe(pipes + 2); // sets up 2nd pipe
//
//   // we now have 4 fds:
//   // pipes[0] = read end of cat->grep pipe (read by grep)
//   // pipes[1] = write end of cat->grep pipe (written by cat)
//   // pipes[2] = read end of grep->cut pipe (read by cut)
//   // pipes[3] = write end of grep->cut pipe (written by grep)
//
//   // Note that the code in each if is basically identical, so you
//   // could set up a loop to handle it.  The differences are in the
//   // indicies into pipes used for the dup2 system call
//   // and that the 1st and last only deal with the end of one pipe.
//
//   // fork the first child (to execute cat)
//
//   if (fork() == 0)
//     {
//       // replace cat's stdout with write part of 1st pipe
//
//       dup2(pipes[1], 1);
//
//       // close all pipes (very important!); end we're using was safely copied
//
//       close(pipes[0]);
//       close(pipes[1]);
//       close(pipes[2]);
//       close(pipes[3]);
//
//       execvp(*cat_args, cat_args);
//     }
//   else
//     {
//       // fork second child (to execute grep)
//
//       if (fork() == 0)
// 	{
// 	  // replace grep's stdin with read end of 1st pipe
//
// 	  dup2(pipes[0], 0);
//
// 	  // replace grep's stdout with write end of 2nd pipe
//
// 	  dup2(pipes[3], 1);
//
// 	  // close all ends of pipes
//
// 	  close(pipes[0]);
// 	  close(pipes[1]);
// 	  close(pipes[2]);
// 	  close(pipes[3]);
//
// 	  execvp(*grep_args, grep_args);
// 	}
//       else
// 	{
// 	  // fork third child (to execute cut)
//
// 	  if (fork() == 0)
// 	    {
// 	      // replace cut's stdin with input read of 2nd pipe
//
// 	      dup2(pipes[2], 0);
//
// 	      // close all ends of pipes
//
// 	      close(pipes[0]);
// 	      close(pipes[1]);
// 	      close(pipes[2]);
// 	      close(pipes[3]);
//
// 	      execvp(*cut_args, cut_args);
// 	    }
// 	}
//     }
//
//   // only the parent gets here and waits for 3 children to finish
//
//   close(pipes[0]);
//   close(pipes[1]);
//   close(pipes[2]);
//   close(pipes[3]);
//
//   for (i = 0; i < 3; i++)
//     wait(&status);
// }
