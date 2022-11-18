#ifndef MAIN_H
#define MAIN_H

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
extern char **environ;
int shell(char **env);
char *_strcpy(char *dest, char *src);
void _print_env(char **env);
char *_getenv(char *name);
char *_strcat(char *dest, char *src);
char *findpath(char *cmnd);
int _strcmp(char *s1, char *s2);

#endif
