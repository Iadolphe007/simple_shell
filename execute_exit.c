#include "shell.h"

/**
 * execute_exit_command - Handles the execution of the "exit" command
 * @argv: The array of command arguments.
 *
 * Return: This function does not return as it exits the program.
 */

int execute_exit_command(char *argv[])
{
int status = 0;
if (argv[1] != NULL)
{
status = atoi(argv[1]);
}
exit(status);
}
