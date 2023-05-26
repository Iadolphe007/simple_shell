#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_PATH_LEN 1024

int main(void);
char *search_command_path(char *command);
char *check_absolute_path(char *command);
char *new_function(char *command);
int exc_command(char *comd);
void tokenize_command(char *command, char **argv, int max_args);
char *get_command_path(char *command);
void execute_command(char *command_path, char **argv);
int string_compare(char *str1, char *str2);

#endif /* SHELL_H */
