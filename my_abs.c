#include "shell.h"

/**
 * my_abs - Calculate the absolute value of an integer.
 * @value: The integer value.
 *
 * This function calculates and returns the absolute
 * value of the given integer. If the value is greater
 * than or equal to zero, the value itself is returned.
 * Otherwise, the negation of the value is returned.
 *
 * Return: The absolute value of the integer.
 */
int my_abs(int value)
{
return (value >= 0 ? value : -value);
}
