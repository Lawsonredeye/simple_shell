#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stddef.h>

void CtrlCHandler(int x);
extern char **environ;
int _strlen(char *s);
void mprint(char *c);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
#endif
