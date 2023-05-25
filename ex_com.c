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
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		write(STDERR_FILENO, "fork\n", 5);
		_exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command_path, argv, NULL);
		write(STDERR_FILENO, "./shell: ", sizeof("./shell: ") - 1);
		perror(argv[0]);
		_exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}
