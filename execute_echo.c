#include "shell.h"

/**
 * execute_echo_command - Handles the execution of the "echo" comman.
 * @argv: The array of command arguments.
 *
 * Return: 0 to indicate successful execution.
 */

int execute_echo_command(char *argv[])
{
int i = 1;
while (argv[i] != NULL)
{
if (argv[i][0] == '$')
{
char *var_name = argv[i] + 1;
char *var_value = user_getenv(var_name);
if (var_value != NULL)
{
write(STDOUT_FILENO, var_value, my_strlen(var_value));
write(STDOUT_FILENO, " ", 1);
}
}
else
{
write(STDOUT_FILENO, argv[i], my_strlen(argv[i]));
write(STDOUT_FILENO, " ", 1);
}
i++;
}
write(STDOUT_FILENO, "\n", 1);
return (0);
}
