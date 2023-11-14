#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stddef.h>

ssize_t _getline(char **lineptr, size_t *n,FILE *stream);
char *_strtok(char *str, const char *delim);
#endif
