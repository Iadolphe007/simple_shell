#include "shell.h"

/**
 * clear_screen - Clears the screen by writing an
 * escape sequence to the standard output.
 */
void clear_screen(void)
{
/* Escape sequence for clearing the screen*/
const char *clear_sequence = "\033[H\033[J";
/* Write the sequence to standard output*/
write(STDOUT_FILENO, clear_sequence, strlen(clear_sequence));
}

/**
 * change_directory - Changes current working directory to the specified path
 * @path: The desired directory path.
 *
 * This function changes the current working directory to the specified path.
 * It also handles special cases such as moving up to parent directory ("..").
 */

void change_directory(char *path)
{

int ret;/* Variable to store the return value of chdir() */

if (path == NULL || string_compare(path, "..") == 0)
{
/* If the path is NULL or "..", move up to the parent directory */
ret = chdir("..");
}
else
{
/* Otherwise, change to the specified directory */
ret = chdir(path);
}

if (ret != 0)
{
/* If the return value of chdir() is not 0, an error occurred */
perror("cd");
}
}

/**
 * exc_command - tokenize the string and create child
 * @comd: paramter pased to function
 *  Return: 0
 */

int exc_command(char *comd)
{
char *argv[BUFFER_SIZE];
char *cmd_path;
int status;
tokenize_command(comd, argv, BUFFER_SIZE);

if (string_compare(argv[0], "exit") == 0)
{
if (argv[1] != NULL)
{
status = atoi(argv[1]);
exit(status);
}
else
{
exit(0);
}
}

if (string_compare(argv[0], "cd") == 0)
{
if (argv[1] != NULL)
{
change_directory(argv[1]);
}
else
{
struct passwd *pw = getpwuid(getuid());
if (pw != NULL)
{
change_directory(pw->pw_dir);
}
}
return (0);
}
else if (string_compare(argv[0], "echo") == 0 && argv[1] != NULL)
{
int i = 1;
while (argv[i] != NULL)
{
if (argv[i][0] == '$')
{
char *var_name = argv[i] + 1;
char *var_value = getenv(var_name);
if (var_value != NULL)
{
write(STDOUT_FILENO, var_value, strlen(var_value));
write(STDOUT_FILENO, " ", 1);
}
}
else
{
write(STDOUT_FILENO, argv[i], strlen(argv[i]));
write(STDOUT_FILENO, " ", 1);
}
i++;
}
write(STDOUT_FILENO, "\n", 1);
}
else
{
cmd_path = get_command_path(argv[0]);

if (cmd_path != NULL)
{
if (string_compare(argv[0], "clear") == 0)
{
clear_screen();
}
else if (string_compare(argv[0], "env") == 0)
{
execute_env_command(environ);
}
else
{
execute_command(cmd_path, argv);
}

free(cmd_path);
}
else
{
write(STDERR_FILENO, "./shell: No such file or directory\n", sizeof("./shell: No such file or directory\n") - 1);
}
}
return (0);
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
