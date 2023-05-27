#include "shell.h"

/**
 * clear_screen - Clears the screen by writing an
 * escape sequence to the standard output.
 */

void clear_screen(void)
{
const char *clear_sequence = "\033[H\033[J";
write(STDOUT_FILENO, clear_sequence, strlen(clear_sequence));
}
