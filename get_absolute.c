#include "shell.h"

/**
 * get_absolute_command_path - Retrieves the absolute
 * path of a command if it is executable.
 * @command: The name of the command.
 *
 * Return: The absolute path of the command if
 * executable, otherwise NULL.
 */

char *get_absolute_command_path(char *command)
{
int i;
char *command_path;
if (access(command, X_OK) == 0)
{
int path_len = 0;
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
