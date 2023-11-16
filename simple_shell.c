#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
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
	pid_t child;
	char *lineptr = NULL, *token = NULL, *temptoken[32];
	int i, chill, lenght = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && ac == 1)
		{
			printf("$ ");
			fflush(stdin);
		}
		/* get cracters from the stdin and store it in a buffer */
		if (_getline(&lineptr, &n, stdin) != -1) /*checking if getline fails */
		{
			lenght = strlen(lineptr);
			if (lenght > 0)
				lineptr[lenght - 1] = '\0';
		}
		else
		{
			if (feof(stdin))
			{
				free(lineptr);
				exit(EXIT_FAILURE);
			}
			perror("Getline failed");
			free(lineptr);
			exit(-1);
		}
		/*storing a temp value in the token to be tokenized/ parsed */
		token = _strtok(lineptr, " ,\n");
		for (i = 0; token != NULL && i < 31; i++)
		{
			temptoken[i] = token;
			token = _strtok(NULL, " ,\n");
		}
		/*put the last element in the temptoken to NULL to indicate end*/
		temptoken[i] = NULL;
		if (temptoken[0] != NULL && strcmp(temptoken[0], "exit") == 0)
			/*check if the tokenized character is exit to close the terminal*/
		{
			free(lineptr);
			printf("Terminal Closed\n");
			exit(0);
		}
		child = fork();
		if (child == -1)
		{
			perror("./hsh");
			free(lineptr);
			exit(1);
		}
		if (child == 0)
		{
			if (temptoken[0] == NULL || strcmp(temptoken[0], "") == 0)
			{
				free(lineptr);
				exit(0);
			}
			/*check if the string entered inside the child process is env*/
			if (strcmp(temptoken[0], "env") == 0)
			{
				for (i = 0; envp[i] != NULL; i++)
				{
					printf("%s\n", envp[i]);
				}
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
