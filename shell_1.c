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
write(STDOUT_FILENO, clear_sequence, my_strlen(clear_sequence));
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
