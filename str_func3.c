#include "shell.h"

/**
 * _isdigit - defines if string passed is a number
 *
 * @str: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}

/**
 * rev_string - reverses a string.
 * @str: input string.
 * Return: no return.
 */
void rev_string(char *str)
{
	int i = 0, j, right;

	while (str[i] != '\0')
	{
		i++;
	}
	j = i / 2;
	right = 0;

	while (right != j)
	{
		char tmp = str[right];
		int left = i - right - 1;

		str[right] = str[left];
		str[left] = tmp;

		right++;
	}
}
