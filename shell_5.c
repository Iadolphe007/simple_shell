#include "shell.h"

int exc_command(char *comd);
void tokenize_command(char *command, char **argv, int max_args);
void execute_command(char *command_path, char **argv);
void execute_env_command(char **environ);
void comd(void);

extern char **environ;

/**
 * string_compare - compare two strings
 * @str1: first string
 * @str2: second string
 * Return: 0 if the strings are equal, a positive value if str1 > str2,
 * and a negative value if str1 < str2
 */
int string_compare(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(const unsigned char *)str1 - *(const unsigned char *)str2);
}

/**
 * exc_command - exectute exit or env command
 * @comd: parameter passed to function
 * Return: 0
 */

int exc_command(char *comd)
{
	char *argv[BUFFER_SIZE];

	tokenize_command(comd, argv, BUFFER_SIZE);

	if (string_compare(argv[0], "exit") == 0)
	{
		return (1);
	}
	if (string_compare(argv[0], "env") == 0)
	{
		execute_env_command(environ);
	}
	return (0);

	execute_command(argv[0], argv);

	return (0);
}
/**
 * tokenize_command - tokenize command string into individual arguments
 * and storing them in the argv array
 * @command: string representing the command to be tokenized
 * @argv: pointer to an array of strings where
 * the tokenized arguments will be stored
 * @max_args: An integer representing the maximum number o
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

	if (pid == -1)
	{
		write(STDERR_FILENO, "fork\n", 5);
		_exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command_path, argv, NULL);
		write(STDERR_FILENO, "execve\n", 7);
		_exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

/**
 * exc_env_command - provide working env
 * @environ: environment parameter
 */
void execute_env_command(char **environ)
{
	char **env;
	ssize_t count;

	for (env = environ; *env != NULL; env++)
	{
		count = 0;
		while ((*env)[count] != '\0')
			count++;

		write(STDOUT_FILENO, *env, count);
		write(STDOUT_FILENO, "\n", 1);
	}

}

/**
 * comd - prompt user for input
 * loop_cont - make loop continue as long as it's equal to one
 * break -  it  Exit the loop if the command is "exit"
 */

void comd(void)
{
	char prompt[] = "$ ";
	char *cmd = NULL;
	ssize_t read_bytes;
	size_t cmd_size = 0;
	int loop_cont = 1;

	while (loop_cont && write(STDOUT_FILENO, prompt, 2))
	{
		read_bytes = getline(&cmd, &cmd_size, stdin);
		if (read_bytes <= 0)
			loop_cont = 0;
		else
		{
			cmd[read_bytes - 1] = '\0';
			if (string_compare(cmd, "exit") == 0)
				break;
			exc_command(cmd);
		}
	}
	free(cmd);
	_exit(EXIT_SUCCESS);
}

/**
 * main - entry point
 *  Return: always 0
 */
int main(void)
{
	comd();
	return (0);
}
