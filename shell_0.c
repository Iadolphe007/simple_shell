#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <pwd.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 1024


/* Function declarations*/
char *get_command_path(char *command);
int string_compare(const char *str1, const char *str2);
void tokenize_command(char *command, char **argv, int max_args);
void execute_command(char *command_path, char **argv);
void execute_env_command(char **environ);
void comd(void);
void change_directory(char *path);
void handle_variable_replacement(char *command, int status);
int builtin_echo(char **args);
int exc_command(char *comd);

/**
 * main - entry point
 *  Return: always 0
 */

int main(void)
{
char prompt[] = "$ ";
char *cmd = NULL;
ssize_t read_bytes;
size_t cmd_size = 0;
int loop_cont = 1;
const char newline[] = "\n";

while (loop_cont && write(STDOUT_FILENO, prompt, sizeof(prompt) - 1))
{
read_bytes = getline(&cmd, &cmd_size, stdin);
if (read_bytes <= 0)
loop_cont = 0;
else
{
cmd[read_bytes - 1] = '\0';
if (string_compare(cmd, "exit") == 0)
break;

/* Handle variable replacement in the command*/
handle_variable_replacement(cmd, 0);

exc_command(cmd);
}
}
free(cmd);
write(STDOUT_FILENO, newline, sizeof(newline) - 1);
return (EXIT_SUCCESS);
}
