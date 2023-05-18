#include "shell.h"

/**
 * exc_command - tokenize the string and create child
 * @comd: paramter pased to function
 *  Return: 0
 */

int exc_command(char *comd)
{
	char *token, *argv[BUFFER_SIZE];
	int argc = 0;
	pid_t pid;

	token = strtok(comd, " ");
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
		waitpid(pid, NULL, 0);
	return (0);
}
/**
 * comd - prompt user for input
 * loop_cont - make loop continue as long as it's equal to one
 *
 */

void comd(void)
{
	char prompt[] = "$ ", cmd[BUFFER_SIZE];
	ssize_t read_bytes;
	int loop_cont = 1;

	while (loop_cont && write(STDOUT_FILENO, prompt, sizeof(prompt) - 1))
	{
		read_bytes = read(STDIN_FILENO, cmd, BUFFER_SIZE - 1);
		if (read_bytes <= 0)
		{
			loop_cont = 0;
		}
		else
		{
			cmd[read_bytes - 1] = '\0';
			exc_command(cmd);
		}
	}
	_exit(EXIT_SUCCESS);
}

/**
 * main - entry point of the program
 * Return: 0
 */
int main(void)
{
	comd();
	return (0);
}
