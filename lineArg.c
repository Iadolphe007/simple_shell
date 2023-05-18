#include "shell.h"

/**
 * main - provide command line
 *  Return: EXIT_SUCCESS on success or EXIT_FAILURE if the execution failed
 */

int command(void)
{
	char prompt[] = "$ ", cmd[BUFFER_SIZE];
	char *token, *argv;
	int stat, argc = 0;
	ssize_t read_bytes;
	pid_t pid;

	while (write(STDOUT_FILENO, prompt, sizeof(prompt) - 1) &&
			(read_bytes = read(STDIN_FILENO, cmd, BUFFER_SIZE - 1)) > 0)
	{
		cmd[read_bytes - 1] = '\0';
		token = strtok(cmd, " ");
		argv[BUFFER_SIZE];
	}
	while (token != NULL && argc < BUFFER_SIZE - 1)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	pid = fork();
	if (pid == -1)
	{
		write(STDERR_FILENO, "fork\n", sizeof("fork\n") - 1);
		_exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (access(argv[0], X_OK) == 0)
		{
			execvp(argv[0], argv);
			write(STDERR_FILENO, "execve\n", sizeof("execve\n") - 1);
		}
		else
		{
			write(STDERR_FILENO, "./shell: No such file or directory\n",
					sizeof("./shell: No such file or directory\n") - 1);
		}
		_exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &stat, 0);
	_exit(EXIT_SUCCESS);
}
