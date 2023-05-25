#include "shell.h"

/**
 * list_to_strings - displays an array of strings of the string linked list
 * @head: pointer to the initial node
 * Return: an array of strings str[]
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = list_len(head), k;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 * print_list - prints out all elements of a list_t, linked list
 * @h: pointer to the initial node
 * Return: size of the list
 */
size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_puts("\n");
		_puts(h->str ? h->str : "(nil)");
		_putchar(' ');

		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_to_starts_with - displays a node whose string starts witha  prefix
 * @node: pointer to head of the list
 * @prefix: comparative string
 * @c: character that follows the prefix to match
 * Return: matched node (Succes), otrherwise Null
 */
list_t *node_to_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_the_node_index - fetches a node's index
 * @head: pointer to head of the list
 * @node: node pointer
 * Return: the node index (success), otherwise,-1
 */
ssize_t get_the_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
