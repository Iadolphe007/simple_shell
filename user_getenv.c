#include "shell.h"

/**
 * user_getenv - Retrieves the value of an environment variable
 * based on its name.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */

char *user_getenv(const char *name)
{
int name_length = strlen(name);
int i;

for (i = 0; environ[i] != NULL; i++)
{
if (my_strncmp(name, environ[i], name_length) == 0 &&
environ[i][name_length] == '=')
{
return (environ[i] + name_length + 1);
}
}

return (NULL);
}
