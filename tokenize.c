#include "shell.h"


/**
 * tokenize_command - tokenize command string into individual arguments
 * and storing them in the argv array
 * @command: string representing the command to be tokenized
 * @argv: pointer to an array of strings where
 * the tokenized arguments will be stored
 * @max_args: An integer representing the maximum number of
 * arguments that can be stored in the argv array
 */

void tokenize_command(char *command, char **argv, int max_args)
{
	int argc = 0;
	char *token = strtok(command, " ");

	while (token != NULL && argc < max_args - 1)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
}

