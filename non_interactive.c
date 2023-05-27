#include "shell.h"

/**
 * execute_non_interactive - Execute a command in non-interactive mode.
 * @args: The array of command arguments.
 * @program_name: The name of the program.
 *
 */

void execute_non_interactive(char **args, char *program_name)
{
size_t program_name_length;
size_t arg_length;
pid_t pid = fork();
if (pid < 0)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/* Child process */
if (execvp(args[0], args) == -1)
{
char error_message[] = "%s: 1: %s: not found\n";
(void)error_message;
program_name_length = my_strlen(program_name);
arg_length = my_strlen(args[0]);
write(STDERR_FILENO, program_name, program_name_length);
write(STDERR_FILENO, ": 1: ", 5);
write(STDERR_FILENO, args[0], arg_length);
write(STDERR_FILENO, ": not found\n", 12);
exit(EXIT_FAILURE);
}
}
else
{
/*Parent process*/
int status;
waitpid(pid, &status, 0);
}
}

/**
 * handle_noninteractive_mode - Handle the non-interactive mode of the program.
 * @filename: The name of the file containing commands.
 * @program_name: The name of the program.
 *
 */

void handle_noninteractive_mode(char *filename, char *program_name)
{
int file = open(filename, O_RDONLY);
char *line = NULL;
size_t line_length = 0;
ssize_t read_bytes;
size_t program_name_length;
size_t filename_length;

if (file == -1)
{
char error_message[] = "%s: %s: No such file or directory\n";
(void)error_message;
program_name_length = my_strlen(program_name);
filename_length = my_strlen(filename);
write(STDERR_FILENO, program_name, program_name_length);
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, filename, filename_length);
write(STDERR_FILENO, ": No such file or directory\n", 27);
exit(EXIT_FAILURE);
}

while ((read_bytes = read(file, line, line_length)) != -1)
{
if (read_bytes == 0)/* End of file*/
break;

line[read_bytes - 1] = '\0';/* Remove newline character*/
read_command(line, program_name);
}

free(line);
close(file);
}

/**
 * read_command - Read and process a command line.
 * @input: The input command line.
 * @program_name: The name of the program.
 *
 * and executes the command if it's not empty.
 */

void read_command(char *input, char *program_name)
{
char *args[MAX_ARGS];
int i = 0;

args[i] = strtok(input, DELIMITERS);
while (args[i] != NULL)
{
i++;
args[i] = strtok(NULL, DELIMITERS);
}

if (args[0] != NULL)
{
execute_non_interactive(args, program_name);
}
}
