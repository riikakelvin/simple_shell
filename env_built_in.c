#include "shell.h"

/**
 * _myhistory - shows history list,(single command by line, followed by
 *              line numbers) starting from 0.
 * @info: Has potential arguments to aid  maintain specific function prototype.
 *  Return: Always 0, when successful
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - deactivates alias from string
 * @info: the parameter struct
 * @str: the string alias converted
 * Return: Always 0 on success, otherwise 1 on failure
 */
int unset_alias(info_t *info, char *str)
{
	char *ptr, ch;
	int outcome;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	outcome = delete_the_node_at_index(&(info->alias),
		get_the_node_index(&(info->alias), node_to_start_with(&(info->alias),
				str, -1)));
	*ptr = ch;
	return (outcome);
}

/**
 * set_alias - Activates alias to string
 * @info: the parameter struct
 * @str: the string alias set
 * Return: Always 0 on success, otherwise, 1 on failure
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_the_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print out alias strings
 * @node: alias node
 * Return: Always 0 when successful, otherwise 1, on failure
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *k = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (k = node->str; k <= ptr; k++)
		{
			_putchar(*a);
			_putchar('\'');
			_puts(p + 1);
			_puts("'\n");

			return (0);
		}
	}
	return (1);
}

/**
 * _myalias - imitates builtin alias
 * @info: Has potential arguments to aid maintain specified function prototype.
 *  Return: Always 0 (sucessful)
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
		{
			set_alias(info, info->argv[i]);
		}
		else
		print_alias(node_to_start_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
