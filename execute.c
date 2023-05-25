#include "shell.h"

/**
 * exc_command - tokenize the string and create child
 * @comd: paramter pased to function
 * Return: 0
 */

int exc_command(char *comd)
{
	char *argv[BUFFER_SIZE];
	char *cmd_path;

	tokenize_command(comd, argv, BUFFER_SIZE);
	cmd_path = get_command_path(argv[0]);

	if (cmd_path != NULL)
	{
		execute_command(cmd_path, argv);
		free(cmd_path);
	}
	else
	{
		write(STDERR_FILENO, "./shell: No such file or directory\n",
				sizeof("./shell: No such file or directory\n") - 1);
	}
	return (0);
}
