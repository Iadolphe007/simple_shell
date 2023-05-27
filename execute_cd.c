#include "shell.h"

/**
 * execute_cd_command - Handles the execution of the "cd" command.
 * @argv: The array of command arguments.
 *
 * Return: 0 to indicate successful execution.
 */

int execute_cd_command(char *argv[])
{
if (argv[1] != NULL)
{
chdir(argv[1]);
}
else
{
char *home_dir = user_getenv("HOME");
if (home_dir != NULL)
{
chdir(home_dir);
}
}
return (0);
}
