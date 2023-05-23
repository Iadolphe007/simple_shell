#include "shell.h"

/**
 * handle_variable_replacement - Replaces specific variables
 * in the command string.
 * @command: The command string to be modified.
 * @status: The exit status of the previous command.
 *
 */

void handle_variable_replacement(char *command, int status)
{
/* Allocate memory for the modified command */
char *result = malloc(MAX_COMMAND_LENGTH);
/* Variables for iteration and indexing */
int i, j = 0;

for (i = 0; command[i] != '\0'; i++)
{
if (command[i] == '$')
{
i++;/* Move to the next character after '$' */

if (command[i] == '?')
{
/*  Replace "$?" with the exit status of the previous command */
sprintf(result + j, "%d", WEXITSTATUS(status));
j += strlen(result + j);/* Update the index */
}
else if (command[i] == '$')
{
/* Replace "$$" with the process ID (PID) of the current process */
sprintf(result + j, "%d", getpid());
j += strlen(result + j);/* Update the index */
}
else
{
result[j++] = '$';
result[j++] = command[i];
}
}
else
{
/* Copy non-variable characters directly to the result */
result[j++] = command[i];
}
}
result[j] = '\0';/*  Add null terminator to the result */
/* Copy the modified command back to the original command string */
strcpy(command, result);
/* Free the memory allocated for the modified command */
free(result);
}

/**
 * builtin_echo - Implementation of the "echo" built-in command.
 * @args: The array of strings representing the command arguments.
 *
 * Return: Always 1 (indicating success).
 */

int builtin_echo(char **args)
{
/* Start from index 1 to skip the command itself */
int i = 1;
/* Variable to store environment variable values */
char *var;
while (args[i] != NULL)
{
/* Check for variable replacement*/
if (args[i][0] == '$')
{
/* Get the value of the environment variable */
var = getenv(args[i] + 1);
if (var != NULL)
{
/* Write the value to standard output */
write(STDOUT_FILENO, var, strlen(var));
/* Separate with a space */
write(STDOUT_FILENO, " ", 1);
}
}
else
{
/* Write the argument to standard output */
write(STDOUT_FILENO, args[i], strlen(args[i]));
/* Separate with a space */
write(STDOUT_FILENO, " ", 1);
}
i++;
}
/* Print a newline character */
write(STDOUT_FILENO, "\n", 1);
/* Return 1 to indicate success*/
return (1);
}
