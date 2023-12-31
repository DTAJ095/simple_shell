#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 * Return: nothing
 */
void free_data(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: nothing
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = auxItoa(getpid());
}

/**
 * main - Entry point
 *
 * @argc: argument count
 * @argv: array contaning the command line arguments
 *
 * Return: Always 0 on success.
 */
int main(int argc, char **argv)
{
	data_shell datash;
	(void) argc;

	signal(SIGINT, get_sign);
	set_data(&datash, argv);
	shellLoop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}

