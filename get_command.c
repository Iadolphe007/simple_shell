#include "shell.h"

/**
 * get_command_path - find full path of the command from dir
 * @command: name of the command for which we want to find the full path.
 * Return: return NULL if the command is not found or
 * it allocated string that contains the full path of the command
 */

char *get_command_path(char *command)
{
char *command_path = get_absolute_command_path(command);

if (command_path == NULL)
command_path = get_relative_command_path(command);

return (command_path);
}
