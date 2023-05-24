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
char result[MAX_COMMAND_LENGTH];
int i, j = 0;
int k;
char exit_status[16];
int exit_status_len;
int temp_status;
char pid_str[16];
int pid_str_len;
int temp_pid;
for (i = 0; command[i] != '\0'; i++)
{
if (command[i] == '$')
{
i++;

if (command[i] == '?')
{
exit_status_len = 0;
temp_status = WEXITSTATUS(status);

if (temp_status == 0)
{
exit_status[exit_status_len++] = '0';
}
else
{
while (temp_status > 0)
{
exit_status[exit_status_len++] = '0' + (temp_status % 10);
temp_status /= 10;
}
}

for (k = exit_status_len - 1; k >= 0; k--)
{
result[j++] = exit_status[k];
}
}
else if (command[i] == '$')
{
pid_str_len = 0;
temp_pid = getpid();

while (temp_pid > 0)
{
pid_str[pid_str_len++] = '0' + (temp_pid % 10);
temp_pid /= 10;
}

for (k = pid_str_len - 1; k >= 0; k--)
{
result[j++] = pid_str[k];
}
}
else
{
result[j++] = '$';
result[j++] = command[i];
}
}
else
{
result[j++] = command[i];
}
}

result[j] = '\0';
my_strcpy(command, result);
}

/**
 * builtin_echo - Implementation of the echo built-in command.
 * @args: The array of strings representing the command arguments.
 *
 * Return: Always 1 (indicating success).
 */

int builtin_echo(char **args)
{
int i = 1;
char *var;
while (args[i] != NULL)
{
/* Check for variable replacement*/
if (args[i][0] == '$')
{
var = user_getenv(args[i] + 1);
if (var != NULL)
{
write(STDOUT_FILENO, var, my_strlen(var));
write(STDOUT_FILENO, " ", 1);
}
}
else
{
write(STDOUT_FILENO, args[i], my_strlen(args[i]));
write(STDOUT_FILENO, " ", 1);
}
i++;
}
write(STDOUT_FILENO, "\n", 1);
return (1);
}
