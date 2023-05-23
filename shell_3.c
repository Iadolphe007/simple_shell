#include "shell.h"

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
