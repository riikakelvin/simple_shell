#include "shell.h"

/**
 * add_node - adds a node to the beginnign of the list
 * @head: pointer address to the head node
 * @str: string field of node
 * @num: node index as used by the history file
 * Return: actual size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - add nodes to  end of the list
 * @head: pointer address to the head node
 * @str: string field of the node
 * @num: node index as used by the history file
 * Return: actual size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the string section of list_t linked list
 * @h: pointer to the initial node
 * Return: actual size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * delete_node_at_index - removes node at specified index
 * @head: pointer address of the initial node
 * @index: index of node to be deleted
 * Return: 1 when successful, otherwise 0 for failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int t = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (t == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		t++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all the nodes on the list
 * @head_ptr: pointer address to the head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

