#include "shell.h"

/**
 * main - print character
 * Return: aleayas 0;
 */

int main(void)
{
	char *mess = "this is simple shell project \n";
	int len = strlen(mess);

	write(1, mess, len);

	return (0);
}
