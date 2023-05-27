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
 * my_strlen - Calculates the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */

int my_strlen(const char *str)
{
int length = 0;

if (str != NULL)
{
do {
length++;
} while (*(str + length) != '\0');
}

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
int i = 0;

if (src != NULL)
{
do {
dest[i] = src[i];
i++;
} while (src[i] != '\0');
}

dest[i] = '\0';

return (dest);
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
size_t i = 0;  /* Variable to track the current index*/

if (n > 0)
{  /* Check if n is greater than 0*/
do {
if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
{
/* If characters are not equal or either string ends, return the difference*/
return (s1[i] - s2[i]);
}
i++;  /* Increment the index*/
/* Continue until reaching the maximum number of characters, n*/
} while (i < n);
}

return (0);  /* Both strings are equal up to n characters*/
}

/**
 * my_strcspn - Calculate the length of the initial segment
 * of a string that does not contain any characters from another string.
 * @s: The input string.
 * @reject: The string of characters to reject.
 *
 * Return: This function returns the length of the initial segment of
 * the string @s that does not contain any characters from the string @reject.
 */
size_t my_strcspn(const char *s, const char *reject)
{
const char *s_ptr = s;
const char *reject_ptr;
size_t count = 0;

while (*s_ptr != '\0')
{
reject_ptr = reject;
while (*reject_ptr != '\0')
{
if (*s_ptr == *reject_ptr)
return (count);/*Return the count on the first match*/
reject_ptr++;
}

s_ptr++;
count++;/*Increment the count for each character in s*/
}

return (count);/*Return the count if no match is found*/
}
