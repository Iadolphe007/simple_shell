#include "shell.h"

/**
 * execute_command - execute command specified by command_path
 * @command_path: A string representing the full
 * path of the command to be executed
 * @argv: pointer to an array of strings representing
 * the arguments to be passed to the command
 */

void execute_command(char *command_path, char **argv)
{
pid_t pid;
int status;
char error_message[] = "%s: 1: %s: not found\n";
(void)error_message;

pid = fork();

if (pid == 0)
{

if (execve(command_path, argv, NULL) == -1)
{
write(STDERR_FILENO, argv[0], my_strlen(argv[0]));
write(STDERR_FILENO, ": 1: ", 5);
write(STDERR_FILENO, argv[0], my_strlen(argv[0]));
write(STDERR_FILENO, ": not found\n", 12);
_exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
char error_message[] = "Fork failed\n";
write(STDERR_FILENO, error_message, my_strlen(error_message));
exit(EXIT_FAILURE);
}
else
{
do {
if (waitpid(pid, &status, WUNTRACED) == -1)
{
char error_message[] = "Waitpid failed\n";
write(STDERR_FILENO, error_message, my_strlen(error_message));
exit(EXIT_FAILURE);
}
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}
