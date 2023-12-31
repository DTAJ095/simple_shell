#include "shell.h"

/**
 * checkEnv - checks if the typed variable is an env variable.
 * @head: head of linked list.
 * @data: data structure.
 * @input: input.
 * Return: no return
 */
void checkEnv(r_var **head, char *input, data_shell *data)
{
	int row, chr, j, len_val;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				len_val = _strlen(_envr[row] + chr + 1);
				add_var_node(head, j, _envr[row] + chr + 1, len_val);
				return;
			}
			if (input[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}
	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' ||
input[j] == '\t' ||
input[j] == ';' ||
input[j] == '\n')
			break;
	}
	add_var_node(head, j, NULL, 0);
}

/**
 * checkVars - check if the typed variable is $$ or $?
 * @head: head of the linked list.
 * @in: input string.
 * @st: last status of the Shell.
 * @data: data structure.
 * Return: no return.
 */
int checkVars(r_var **head, char *in, char *st, data_shell *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_node(head, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var_node(head, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var_node(head, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_node(head, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_node(head, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_node(head, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_node(head, 0, NULL, 0);
			else
				checkEnv(head, in + i, data);
		}
	}
	return (i);
}

/**
 * replacedInput - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @new_len: new length
 * Return: replaced string
 */
char *replacedInput(r_var **head, char *input, char *new_input, int new_len)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < new_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = auxItoa(datash->status);
	head = NULL;
	olen = checkVars(&head, input, status, datash);
	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;
	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}
	nlen += olen;
	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replacedInput(&head, input, new_input, nlen);
	free(input);
	free(status);
	free_var_list(&head);
	return (new_input);
}
