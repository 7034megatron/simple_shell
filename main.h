#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void execute_command(char *tokens[]);
int handle_builtin_command(char *tokens[]);
void display_prompt(const char *prompt);
int run_shell(const char *prompt, char *name_file);
void print_environment(void);
char *search_path(const char *command);
int _strncmp(char *s1, char *s2, size_t n);

extern char **environ;

#endif
