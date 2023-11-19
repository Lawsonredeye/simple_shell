#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
int main(int ac, char *envp[]);

/**
 * main - a simplified version of the shell
 * that works in similar ways but dont do all the complex task
 * that the shell does.
 * @ac: argument count
 * @envp: environment variable
 * Return: 0 Always
 */
int main(int ac, char *envp[])
{
	size_t n = 0;
	pid_t child;
	char *lineptr = NULL, *token = NULL, *temptoken[32];
	int i, status, chill, length = 0;
	char *path, *dir, *executable_path;

	signal(SIGINT, CtrlCHandler);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && ac == 1)
	{
		printf("$ ");
		fflush(stdout);
	}
	while (1)
	{
		if (_getline(&lineptr, &n, stdin) != -1)
		{
			length = strlen(lineptr);
			if (length > 0)
				lineptr[length - 1] = '\0';
		}
		else
		{
			if (feof(stdin))
			{
				free(lineptr);
				exit(EXIT_FAILURE);
			}
			perror("./hsh");
			free(lineptr);
			exit(EXIT_FAILURE);
		}
		token = _strtok(lineptr, " ");
		for (i = 0; token != NULL && i < 31; i++)
		{
			temptoken[i] = token;
			token = _strtok(NULL, " ");
		}
		temptoken[i] = NULL;
		if (temptoken[0] != NULL && strcmp(temptoken[0], "exit") == 0)
		{
			free(lineptr);
			printf("Shell Closed\n");
			exit(0);
		}
		child = fork();
		if (child == -1)
		{
			perror("./hsh");
			free(lineptr);
			return (-1);
		}
		if (child == 0)
		{
			if (temptoken[0] != NULL && strcmp(temptoken[0], "env") == 0)
			{
				for (i = 0; environ[i] != NULL; i++)
				{
					printf("%s\n", environ[i]);
				}
				free(lineptr);
				exit(0);
			}
			if (temptoken[0] == NULL || strcmp(temptoken[0], "") == 0)
			{
				free(lineptr);
				exit(0);
			}
			if (strchr(temptoken[0], '/') != NULL)
			{
				if (execve(temptoken[0], temptoken, envp) == -1)
				{
					perror("./hsh");
					free(lineptr);
					exit(EXIT_FAILURE);
				}
			}
			path = getenv("PATH");
			if (path == NULL)
			{
				fprintf(stderr, "./hsh\n");
				free(lineptr);
				exit(EXIT_FAILURE);
			}
			dir = strtok(path, ":");
			while (dir != NULL)
			{
				executable_path = malloc(strlen(dir) + strlen(temptoken[0]) + 2);
				if (executable_path == NULL)
				{
					perror("./hsh failed");
					free(lineptr);
					exit(EXIT_FAILURE);
				}
				strcpy(executable_path, dir);
				strcat(executable_path, "/");
				strcat(executable_path, temptoken[0]);

				if (access(executable_path, X_OK) == 0)
				{
					if (execve(executable_path, temptoken, envp) == -1)
					{
						perror("./hsh");
						free(lineptr);
						exit(EXIT_FAILURE);
					}
				}

				free(executable_path);
				dir = strtok(NULL, ":");
			}
			perror("./hsh");
			/*fprintf(stderr, "Command not found: %s\n", temptoken[0]);*/
			free(lineptr);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&chill);
			if (WIFEXITED(chill))
			{
				status = WEXITSTATUS(chill);
			}
		}
		printf("$ ");
	}
	printf("\n");
	free(lineptr);
	return (status);
}
