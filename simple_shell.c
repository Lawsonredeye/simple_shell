#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>
int main(int ac, char *envp[]);

/**
 * main - a simplified version of the shell
 * that works in similar ways but dont do all the complex task
 * that the shell does.
 * @ac: argument count
 * @av: argument vector from the command line
 * @envp: environment variable
 * Return: 0 Always
 */
int main(int ac, char *envp[])
{
	size_t n = 0;
	ssize_t dline;
	pid_t child;
	char *lineptr = NULL, *token = NULL, *temptoken[32];
	int i, j, chill;
	(void) ac;

	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}
		/* get cracters from the stdin and store it in a buffer */
		dline = _getline(&lineptr, &n, stdin);
		if (dline == -1) /*checking if getline fails */
		{
			perror("Error line");
			free(lineptr);
			return (-1);
		}
		/*storing a temp value in the token to be tokenized/ parsed */
		token = _strtok(lineptr, " \n");
		for (i = 0; token != NULL; i++)
		{
			temptoken[i] = token;
			token = _strtok(NULL, " \n");
		}
		/*put the last element in the temptoken to NULL to indiacte end*/
		temptoken[i] = NULL;
		if (strcmp(temptoken[0], "exit") == 0)
		/*check if the tokenized character is exit to close the terminal*/
		{
			free(lineptr);
			printf("Terminal Closed\n");
			exit(EXIT_SUCCESS);
		}
		child = fork();
		if (child == -1)
		{
			perror("./hsh");
			return (-1);
		}
		if (child == 0)
		{
			/*check if the string entered inside the child process is env*/
			if (strcmp(temptoken[0], "env") == 0)
			{
				for (j = 0; envp[j] != NULL; j++)
				{
					printf("%s\n", envp[j]);
				}
				envp[j] = NULL;
				free(lineptr);
				exit(EXIT_SUCCESS);
			}
			if (execve(temptoken[0], temptoken, NULL) == -1)
			/*checks if the execve fails to stop the program*/
			{
				perror("./hsh here");
				free(lineptr);
				return (-1);
			}
		}
		else
		{
			wait(&chill);
		}
	}
	printf("\n");
	free(lineptr);
	return (0);
}
