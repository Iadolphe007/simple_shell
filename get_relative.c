#include "shell.h"

/**
 * get_relative_command_path - Retrieves the relative path of a
 * command if it is executable.
 * @command: The name of the command.
 *
 * Return: The relative path of the command if executable, otherwise NULL.
 */

char *get_relative_command_path(char *command)
{
int j, i;
int path_len;
int command_len;
char *command_path;
char *dir = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
while (dir != NULL && *dir != '\0')
{
int dir_len = 0;
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
