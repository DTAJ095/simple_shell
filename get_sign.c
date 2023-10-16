#include "shell.h"

/**
 * getSigint - Handle the crtl + c call in prompt
 * @signal: Signal handler
 */
void get_sign(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n(Eshell)$ ", 10);
}

