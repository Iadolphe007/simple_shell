#include "shell.h"

/**
 * string_compare - compare two strings
 * @str1: first string
 * @str2: second string
 * Return: 0 if the strings are equal, a positive value if str1 > str2,
 * and a negative value if str1 < str2
 */

int string_compare(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (*str1 == '\0' && *str2 == '\0');
}
