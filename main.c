#include "shell.h"

/**
 * main - prompt user for input
 * Return: 0
 * loop_cont - make loop continue as long as it's equal to one
 * break -  it  Exit the loop if the command is "exit"
 */

int main(void)
{
	char command[BUFFER_SIZE];
	ssize_t read_status;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", sizeof("$ ") - 1);
		read_status = read(STDIN_FILENO, command, BUFFER_SIZE);
		if (read_status > 0)
		{
			command[read_status - 1] = '\0';
			if (string_compare(command, "exit"))
				break;
			exc_command(command);

		}
		else
			break;
	}
	return (0);
}
