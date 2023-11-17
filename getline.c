#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>
/**
 * _getline -  reads an entire line from stream, storing the
 * address of the buffer containing the text into *lineptr.
 * @lineptr: buffer containing text
 * @n: size of the buffer
 * @stream: where the file is being read from
 * Return: the number of character read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer;
	char *temp, *file_gets;
	size_t buff_size, char_read;

	if (*n == 0)
		*n = 1024;
	if (*lineptr == NULL)
	{
		buffer = malloc(sizeof(char) * (*n));
		if (buffer == NULL)
			return (-1);
		*lineptr = buffer;
	}
	buff_size = *n;
	file_gets = fgets(*lineptr, *n, stream);
	if (file_gets == NULL)
	{
		if (ferror(stream))
		{
			perror("Error");
			free(*lineptr);
		}
		return (-1);
	}
	char_read = strlen(*lineptr);
	if (char_read > 1)
	{
		if (char_read >= buff_size - 1)
		{
			buff_size *= 2;
			temp = realloc(*lineptr, buff_size);
			if (temp == NULL)
			{
				free(*lineptr);
				return (-1);
			}
			else
			{
				*lineptr = temp;
				*n = buff_size;
			}
		}
		return (char_read);
	}
	else
	{
		*lineptr[0] = '\0';
		return (0);
	}
}
