#include "shell.h"

/**
 * execute_env_command - provide working env
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
