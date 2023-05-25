#include "shell.h"

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
	int dir_len, i, j, command_len, path_len;
	
	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			command_len = 0;
			while (command[command_len] != '\0')
				command_len++;
			command_path = (char *)malloc(command_len + 1);
			if (command_path == NULL)
			{
				perror("malloc");
				_exit(EXIT_FAILURE);
			}
			for (i = 0; i <= command_len; i++)
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
