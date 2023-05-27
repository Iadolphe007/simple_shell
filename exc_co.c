#include "shell.h"

/**
 * exc_command - tokenize the string and create child
 * @comd: paramter pased to function
 *  Return: 0
 */

int exc_command(char *comd)
{
char **argv = malloc(MAX_COMMAND_LENGTH * sizeof(char *));
tokenize_command(comd, argv, MAX_COMMAND_LENGTH);

if (argv[0] == NULL)
{
free(argv);
return (0);
}

if (string_compare(argv[0], "exit") == 0)
{
return (execute_exit_command(argv));
}
else if (string_compare(argv[0], "cd") == 0)
{
execute_cd_command(argv);
}
else if (string_compare(argv[0], "echo") == 0)
{
execute_echo_command(argv);
}
else if (string_compare(argv[0], "clear") == 0)
{
clear_screen();
}
else if (string_compare(argv[0], "env") == 0)
{
execute_env_command(environ);
}
else
{
execute_other_command(argv);
}

free(argv);
return (0);
}
