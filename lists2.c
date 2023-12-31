#include "shell.h"

/**
 * add_var_node - adds a variable at the end
 * @head: head of the linked list.
 * @len_var: length of the variable.
 * @var: value of the variable.
 * @len_val: length of the value.
 * Return: address of the head.
 */
r_var *add_var_node(r_var **head, int len_var, char *var, int len_val)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = len_var;
	new->val = var;
	new->len_val = len_val;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_var_list - frees a r_var list
 * @head: head of the linked list.
 * Return: nothing.
 */
void free_var_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

