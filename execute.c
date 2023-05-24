#include "shell.h"

/**
 * exc_command - tokenize the string and create child
 * @comd: paramter pased to function
 *  Return: 0
 */
int exc_command(char *comd)
{
char *argv[BUFFER_SIZE];
tokenize_command(comd, argv, BUFFER_SIZE);

if (string_compare(argv[0], "exit") == 0)
{
return (execute_exit_command(argv));
}

if (string_compare(argv[0], "cd") == 0)
{
return (execute_cd_command(argv));
}

if (string_compare(argv[0], "echo") == 0 && argv[1] != NULL)
{
return (execute_echo_command(argv));
}

return (execute_other_command(argv));
}

/**
 * execute_exit_command - Handles the execution of the "exit" command
 * @argv: The array of command arguments.
 *
 * Return: This function does not return as it exits the program.
 */
int execute_exit_command(char *argv[])
{
int status;
/*Check if an argument is provided after the "exit" command*/
if (argv[1] != NULL)
{
/*Convert the argument to an integer using `atoi`*/
status = atoi(argv[1]);
/*Terminate the program with the specified status*/
exit(status);
}
else
{
/*Terminate the program with a status of 0*/
exit(0);
}
}

/**
 * execute_cd_command - Handles the execution of the "cd" command.
 * @argv: The array of command arguments.
 *
 * Return: 0 to indicate successful execution.
 */
int execute_cd_command(char *argv[])
{
/*Check if an argument is provided after the "cd" command*/
if (argv[1] != NULL)
{
/*Change the current working directory to the specified path*/
chdir(argv[1]);
}
else
{
/*Attempt to retrieve the home directory*/
char *home_dir = user_getenv("HOME");
/*Check if the home directory is retrieved successfully*/
if (home_dir != NULL)
{
/*Change the current working directory to the home directory*/
chdir(home_dir);
}
}
/*Return 0 to indicate successful execution*/
return (0);
}

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

/**
 * execute_other_command - Handles the execution of other commands.
 * @argv: The array of command arguments.
 *
 * Return: 0 to indicate successful execution.
 */

int execute_other_command(char *argv[])
{
char *cmd_path = get_command_path(argv[0]);

if (cmd_path != NULL)
{
if (string_compare(argv[0], "clear") == 0)
{
/*Call the clear_screen function to clear the screen*/
clear_screen();
}
else if (string_compare(argv[0], "env") == 0)
{
/*Call the execute_env_command function to display environment variables*/
execute_env_command(environ);
}
else
{
/*Call the execute_command function to execute the command*/
execute_command(cmd_path, argv);
}

free(cmd_path);
}
else
{
write(STDERR_FILENO, "./shell: No such file or directory\n", sizeof("./shell: No such file or directory\n") - 1);
}

return (0);
}
