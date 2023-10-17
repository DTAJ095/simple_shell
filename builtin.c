#include "shell.h"

/**
 * getBuiltin - builtin that pass the command in the argument
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*getBuiltin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{"env", _env},
		{"exit", exitShell},
		{"setenv", _cmpenv},
		{"unsetenv", _unsetenv},
		{"cd", cdShell},
		{"help", get_help},
		{NULL, NULL}
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].func);
}
