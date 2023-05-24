#include "shell.h"

/**
 * my_strlen - Calculates the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int my_strlen(const char *str)
{
/* Variable to store the length of the string*/
int length = 0;

if (str != NULL)
{
/* Check if the string is not NULL*/
do {
length++;/* Increment the length*/
} while (*(str + length) != '\0');
}
/* Return the length of the string*/
return (length);
}

/**
 * my_strcpy - Copies a string from source to destination.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: The destination string.
 */
char *my_strcpy(char *dest, char *src)
{
int i = 0;/* Variable to track the current index*/

if (src != NULL)
{ /* Check if the source string is not NULL*/
do {
/* Copy the character from source to destination*/
dest[i] = src[i];
i++;  /* Increment the index*/
} while (src[i] != '\0');
}
/* Ensure the destination string is null-terminated*/
dest[i] = '\0';

return (dest);/* Return the destination string*/
}

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
/* Length of the name*/
int name_length = my_strlen(name);
int i;/*Loop variable*/

/*Iterate through the environment variables*/
for (i = 0; environ[i] != NULL; i++)
{
if (my_strncmp(name, environ[i], name_length) == 0 && environ[i][name_length] == '=')
{
/*If name matches and the character following the name is '=', return value*/
return (environ[i] + name_length + 1);
}
}
/*Return NULL if the environment variable is not found*/
return (NULL);
}

/**
 * my_strncmp - Compares two strings up to a specified number of characters.
 * @s1: The first string.
 * @s2: The second string.
 * @n: The maximum number of characters to compare.
 *
 * Return: The comparison result as an integer.
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
size_t i = 0;/* Variable to track the current index*/

if (n > 0)
{
/* Check if n is greater than 0*/
do {
if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
{
/* If characters are not equal or either string ends, return the difference*/
return (s1[i] - s2[i]);
}
i++;  /* Increment the index*/
} while (i < n);

}

return (0);/* Both strings are equal up to n characters*/
}
