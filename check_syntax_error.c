#include "shell.h"

/**
 * repeated_char - counts the number of appearance
 * of a character
 * @input: input string
 * @idx: index
 * Return: repetitions
 */
int repeated_char(char *input, int idx)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, idx + 1));

	return (idx);
}

/**
 * error_sep - finds syntax errors
 *
 * @input: input string
 * @idx: index
 * @last: last character readed
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep(char *input, int idx, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep(input + 1, idx + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (idx);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (idx);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (idx);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (idx);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (idx);
		}
	}

	return (error_sep(input + 1, idx + 1, *input));
}

/**
 * first_char - finds index of the first character
 *
 * @input: input string
 * @idx: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *idx)
{

	for (*idx = 0; input[*idx]; *idx += 1)
	{
		if (input[*idx] == ' ' || input[*idx] == '\t')
			continue;

		if (input[*idx] == ';' || input[*idx] == '|' || input[*idx] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * printSyntaxError - prints message when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @idx: index of the error
 * @boolean: to control msg error
 * Return: no return
 */
void printSyntaxError(data_shell *datash, char *input, int idx, int boolean)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[idx] == ';')
	{
		if (boolean == 0)
			msg = (input[idx + 1] == ';' ? ";;" : ";");
		else
			msg = (input[idx - 1] == ';' ? ";;" : ";");
	}

	if (input[idx] == '|')
		msg = (input[idx + 1] == '|' ? "||" : "|");

	if (input[idx] == '&')
		msg = (input[idx + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = auxItoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * checkSyntaxError - function to find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int checkSyntaxError(data_shell *datash, char *input)
{
	int start = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(input, &start);
	if (f_char == -1)
	{
		printSyntaxError(datash, input, start, 0);
		return (1);
	}
	i = error_sep(input + start, 0, *(input + start));
	if (i != 0)
	{
		printSyntaxError(datash, input, start + i, 1);
		return (1);
	}
	return (0);
}

