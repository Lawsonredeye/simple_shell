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
 * @envp: environment variable
 * Return: 0 Always
 */
int main(int ac, char *envp[]) {
	size_t n = 0;
	pid_t child;
	char *lineptr = NULL, *token = NULL, *temptoken[32];
	int i, status, chill, length = 0;

	while (1) {
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && ac == 1) {
			printf("$ ");
			fflush(stdout);
		}

		if (_getline(&lineptr, &n, stdin) != -1) {
			length = strlen(lineptr);
			if (length > 0)
				lineptr[length - 1] = '\0';
		} else {
			if (feof(stdin)) {
				free(lineptr);
				exit(EXIT_FAILURE);
			}
			perror("Getline failed");
			free(lineptr);
			exit(1);
		}

		token = strtok(lineptr, " ");
		for (i = 0; token != NULL && i < 31; i++) {
			temptoken[i] = token;
			token = strtok(NULL, " ");
		}

		temptoken[i] = NULL;
		if (temptoken[0] != NULL && strcmp(temptoken[0], "exit") == 0) {
			free(lineptr);
			printf("Terminal Closed\n");
			exit(0);
		}

		child = fork();
		if (child == -1) {
			perror("./hsh");
			free(lineptr);
			return (-1);
		}

		if (child == 0) {
			if (temptoken[0] == NULL || strcmp(temptoken[0], "") == 0) {
				free(lineptr);
				exit(0);
			}

			if (strcmp(temptoken[0], "env") == 0) {
				for (i = 0; envp[i] != NULL; i++) {
					printf("%s\n", envp[i]);
				}
				free(lineptr);
				exit(EXIT_SUCCESS);
			}

			if (execve(temptoken[0], temptoken, envp) == -1) {
				perror("./hsh here");
				free(lineptr);
				exit(EXIT_FAILURE);
			}
		} else {
			wait(&chill);
			if (WIFEXITED(chill)) {
				status = WEXITSTATUS(chill);
			}
		}
	}

	printf("\n");
	free(lineptr);
	return (status);
}
