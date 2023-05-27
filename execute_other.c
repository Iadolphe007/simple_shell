#include "shell.h"

/**
 * execute_other_command - Handles the execution of other commands.
 * @argv: The array of command arguments.
 *
 * Return: 0 to indicate successful execution.
 */

int execute_other_command(char *argv[])
{
char *command_path = get_command_path(argv[0]);
char error_message[] = "%s: 1: %s: not found\n";
(void)error_message;
if (command_path == NULL)
{
write(STDERR_FILENO, argv[0], my_strlen(argv[0]));
write(STDERR_FILENO, ": 1: ", 5);
write(STDERR_FILENO, argv[0], my_strlen(argv[0]));
write(STDERR_FILENO, ": not found\n", 12);
return (-1);
}

execute_command(command_path, argv);
free(command_path);
return (0);
}
