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
#include <stddef.h>

#define BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 1024
#define ARGS_MAX 100
#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define DELIMITERS " \t\r\n\a"

/* Function declarations*/
char *get_command_path(char *command);
int string_compare(const char *str1, const char *str2);
void tokenize_command(char *command, char **argv, int max_args);
void execute_command(char *command_path, char **argv);
void execute_env_command(char **environ);
void comd(void);
void clear_screen(void);
void change_directory(char *path);
void handle_variable_replacement(char *command, int status);
int builtin_echo(char **args);
int exc_command(char *comd);
int my_strlen(const char *str);
char *my_strcpy(char *dest, char *src);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *user_getenv(const char *name);
int execute_exit_command(char *argv[]);
int execute_cd_command(char *argv[]);
int execute_echo_command(char *argv[]);
int execute_other_command(char *argv[]);
char *get_command_path(char *command);
char *get_absolute_command_path(char *command);
char *get_relative_command_path(char *command);
int my_abs(int value);
void read_command(char *input, char *program_name);
void execute_non_interactive(char **args, char *program_name);
void handle_noninteractive_mode(char *filename, char *program_name);
size_t my_strcspn(const char *s, const char *reject);


/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *  Return: always 0
 */

int main(int argc, char *argv[])
{
char *cmd = NULL;
size_t cmd_size = 0;
ssize_t read_bytes;
int loop_cont = 1;
const char prompt[] = "$ ";
const char newline[] = "\n";
char *program_name = argv[0];

if (argc > 1)
{
/* Non-interactive mode*/
handle_noninteractive_mode(argv[1], program_name);
}
else if (isatty(STDIN_FILENO) == 0)
{
/* Interactive mode*/
char *input = NULL;
size_t input_length = 0;
while (1)
{
if (getline(&input, &input_length, stdin) == -1)
{
break;
}
input[my_strcspn(input, "\n")] = '\0';/*Remove newline character*/

if (string_compare(input, "exit") == 0)
{
break;
}

read_command(input, program_name);
}
free(input);
}

else
{
/* Interactive mode */
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

handle_variable_replacement(cmd, 0);
exc_command(cmd);
}
}

free(cmd);
write(STDOUT_FILENO, newline, sizeof(newline) - 1);
}

return (EXIT_SUCCESS);
}
