#include "shell.h"

/**
 * withoutComment - deletes comments from the input
 *
 * @input: input string
 * Return: input without comments
 */
char *withoutComment(char *input)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		input = _realloc(input, i, up_to + 1);
		input[up_to] = '\0';
	}

	return (input);
}

/**
 * shellLoop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shellLoop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "(Eshell)$ ", 10);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = withoutComment(input);
			if (input == NULL)
				continue;

			if (checkSyntaxError(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

