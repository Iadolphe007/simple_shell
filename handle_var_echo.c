#include "shell.h"

/**
 * int_to_str - Convert an integer to a string representation.
 * @value: The integer value to convert.
 * @str: The character array to store the string representation.
 * @len: A pointer to an integer to store the length of the string.
 *
 * Return: None.
 */

void int_to_str(int value, char *str, int *len)
{
int n = my_abs(value);/*Get the absolute value of the integer*/
int i = 0;
int j;
int k;
char temp;

if (n == 0)
{
str[i++] = '0';/*If the value is zero, store '0' in the string*/
}
else
{
while (n > 0)
{
/*Convert each digit to character and store it in the string*/
str[i++] = '0' + (n % 10);
n /= 10;/*Divide the number by 10 to move to the next digit*/
}
}

if (value < 0)
{
str[i++] = '-';/*If the value is negative, store '-' in the string*/
}

*len = i;/*Store the length of the string*/
str[i] = '\0';/*Null-terminate the string*/

/* Reverse the string*/
j = 0;
k = i - 1;
while (j < k)
{
temp = str[j];
str[j] = str[k];
str[k] = temp;
j++;
k--;
}
}

/**
 * replace_exit_status - Replace the exit status in a string with
 * the actual exit status value.
 * @result: The string where the exit status should be replaced.
 * @status: The exit status value.
 *
 * Return: None.
 */

void replace_exit_status(char *result, int status)
{
int exit_status_len;
char exit_status[16];
int temp_status = WEXITSTATUS(status);

int_to_str(temp_status, exit_status, &exit_status_len);

my_strcpy(result, exit_status);
}

/**
 * replace_process_id - Replace the process ID placeholder in a
 * string with the actual process ID value.
 * @result: The string where the process ID should be replaced.
 *
 * Return: None.
 */
void replace_process_id(char *result)
{
int pid_str_len;
char pid_str[16];
int temp_pid = getpid();

int_to_str(temp_pid, pid_str, &pid_str_len);

my_strcpy(result, pid_str);
}

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
int j = 0;
int i;

for (i = 0; command[i] != '\0'; i++)
{
if (command[i] == '$')
{
i++;
if (command[i] == '?')
{
replace_exit_status(&result[j], status);
j += strlen(&result[j]);
}
else if (command[i] == '$')
{
replace_process_id(&result[j]);
j += strlen(&result[j]);
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
/* Assuming the existence of the my_strcpy function*/
my_strcpy(command, result);
}

/**
 * builtin_echo - Implementation of the "echo" built-in command.
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
