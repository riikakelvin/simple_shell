#include "shell.h"

/**
 * list_to_strings - displays an array of strings of the list->stri
 * @head: pointer to the initial node
 * Return: an array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t t = list_len(head), k;
	char **stris;
	char *stri;

	if (!head || !t)
		return (NULL);
	stris = malloc(sizeof(char *) * (t + 1));
	if (!stris)
		return (NULL);
	for (t = 0; node; node = node->next, t++)
	{
		stri = malloc(_strlen(node->stri) + 1);
		if (!stri)
		{
			for (k = 0; k < t; k++)
				free(stris[k]);
			free(stris);
			return (NULL);
		}

		stri = _strcpy(stri, node->stri);
		stris[t] = stri;
	}
	stris[t] = NULL;
	return (stris);
}


/**
 * print_list - prints all sections of list_t linked list
 * @h: pointer to the initial node
 * Return: actual size of the list
 */
size_t print_list(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_puts(h->str ? h->str : "(nil)");
		_putchar(' ');
		_puts("\n");
		h = h->next;
		t++;
	}
	return (t);
}

/**
 * node_starts_with - displays a node whose string starts with the prefix
 * @node: pointer to the list head
 * @c: character following the prefix to match
 * @prefix: string to match with
 * Return: matched node (success),otherwise  null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - fetches the a node's index
 * @head: pointer to the list head
 * @node: pointer to node
 * Return: index of node (success), otherwise -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t t = 0;

	while (head)
	{
		if (head == node)
			return (t);
		head = head->next;
		t++;
	}
	return (-1);
}
/**
 * list_len - shows the length of linked list
 * @h: pointer to the initial node
 * Return: actual size of the list
 */
size_t list_len(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		h = h->next;
		t++;
	}
	return (t);
}

