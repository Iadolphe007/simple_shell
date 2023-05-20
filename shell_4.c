#include "shell.h"

int exc_command(char *comd);
void tokenize_command(char *command, char **argv, int max_args);
char *get_command_path(char *command);
void execute_command(char *command_path, char **argv);
int string_compare(char *str1, char *str2);

/**
 * exc_command - tokenize the string and create child
 * @comd: parameter passed to function
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
 * get_command_path - find full path of the command from dir
 * @command: name of the command for which we want to find the full path.
 * Return: return NULL if the command is not found or
 * it allocated string that contains the full path of the command
 */

char *get_command_path(char *command)
{
	char *dir = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	char *command_path;
	int dir_len, i, j, path_len, command_len;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			path_len = 0;
			while (command[path_len] != '\0')
				path_len++;
			command_path = (char *)malloc(path_len + 1);

			if (command_path == NULL)
			{
				perror("malloc");
				_exit(EXIT_FAILURE);
			}
			for (i = 0; i <= path_len; i++)
				command_path[i] = command[i];
			return (command_path);
		}
		return (NULL);
	}
	while (dir != NULL && *dir != '\0')
	{
		dir_len = 0;
		while (dir[dir_len] != '\0' && dir[dir_len] != ':')
			dir_len++;
		command_len = 0;
		while (command[command_len] != '\0')
			command_len++;
		path_len = dir_len + command_len + 2;
		command_path = (char *)malloc(path_len);

		if (command_path == NULL)
		{
			perror("malloc");
			_exit(EXIT_FAILURE);
		}
		for (i = 0; i < dir_len; i++)
			command_path[i] = dir[i];
		command_path[i++] = '/';

		for (j = 0; command[j] != '\0'; j++, i++)
			command_path[i] = command[j];
		command_path[i] = '\0';

		if (access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);

		if (dir[dir_len] == ':')
			dir += (dir_len + 1);
		else
			dir = NULL;
	}
	return (NULL);
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
 * string_compare - compare two strings
 * @str1: first string
 * @str2: second string
 * Return: 0 if the strings are equal, a positive value if str1 > str2,
 * and a negative value if str1 < str2
 */

int string_compare(char *str1, char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
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
