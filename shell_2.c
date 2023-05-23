#include "shell.h"

/**
 * tokenize_command - tokenize command string into individual arguments
 * and storing them in the argv array
 * @command: string representing the command to be tokenized
 * @argv: pointer to an array of strings where
 * the tokenized arguments will be stored
 * @max_args: An integer representing the maximum number of
 * arguments that can be stored in the argv array
 */

void tokenize_command(char *command, char **argv, int max_args)
{
int argc = 0;
char *token = strtok(command, " ");

while (token != NULL && argc < max_args - 1)
{
if (token[0] == '#')  /*Ignore tokens starting with # */
{
break;  /* Stop processing further tokens*/
}

argv[argc++] = token;
token = strtok(NULL, " ");
}
argv[argc] = NULL;
}

/**
 * get_command_path - find full path of the command from dir
 * @command: name of the command for which we want to find the full path.
 * Return: return NULL if the command is not found or
 * it allocated string that contains the full path of the command
 */

char *get_command_path(char *command)
{
char *dir = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
char *command_path;
int dir_len, i, j, path_len, command_len;

if (command[0] == '/')
{
if (access(command, X_OK) == 0)
{
path_len = 0;
while (command[path_len] != '\0')
path_len++;
command_path = (char *)malloc(path_len + 1);

if (command_path == NULL)
{
perror("malloc");
_exit(EXIT_FAILURE);
}
for (i = 0; i <= path_len; i++)
command_path[i] = command[i];
return (command_path);
}
return (NULL);
}
while (dir != NULL && *dir != '\0')
{
dir_len = 0;
while (dir[dir_len] != '\0' && dir[dir_len] != ':')
dir_len++;
command_len = 0;

while (command[command_len] != '\0')
command_len++;

path_len = dir_len + command_len + 2;
command_path = (char *)malloc(path_len);

if (command_path == NULL)
{
perror("malloc");
_exit(EXIT_FAILURE);
}

for (i = 0; i < dir_len; i++)
command_path[i] = dir[i];
command_path[i++] = '/';

for (j = 0; command[j] != '\0'; j++, i++)
command_path[i] = command[j];
command_path[i] = '\0';

if (access(command_path, X_OK) == 0)
return (command_path);
free(command_path);

if (dir[dir_len] == ':')
dir += (dir_len + 1);
else
dir = NULL;
}
return (NULL);
}

/**
 * execute_command - execute command specified by command_path
 * @command_path: A string representing the full
 * path of the command to be executed
 * @argv: pointer to an array of strings representing
 * the arguments to be passed to the command
 */

void execute_command(char *command_path, char **argv)
{
pid_t pid = fork();

if (pid == -1)
{
write(STDERR_FILENO, "fork\n", 5);
_exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execve(command_path, argv, NULL);
write(STDERR_FILENO, "execve\n", 7);
_exit(EXIT_FAILURE);
}
else
{
waitpid(pid, NULL, 0);
}
}
