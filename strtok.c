#include <string.h>
#include "main.h"
/**
 * _strtok - function that tokenize a string
 * @str: string to be tokenized
 * @delim: a delimiter that should be removed from the string
 *
 * Return: returns a pointer that marks the
 * beginning of current token in the string
 */
char *_strtok(char *str, const char *delim)
{
	static char *marker;
	char *start_token;
	int i, j;

	if (str != NULL)
		marker = str;
	if (marker == NULL)
		return (NULL);
	start_token = marker;
	for (i = 0; marker[i] != '\0'; i++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (marker[i] == delim[j])
			{
				marker[i] = '\0';
				marker = &marker[i + 1];
				if (*marker == '\0')
				{
					marker = NULL;
				}
				return (start_token);
				break;
			}
		}
	}
	if (marker[i] == '\0')
		marker = NULL;
	return(start_token);
}
