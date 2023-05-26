#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t t = *p;

	if (buf[t] == '|' && buf[t + 1] == '|')
	{
		buf[t] = 0;
		t++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[t] == '&' && buf[t + 1] == '&')
	{
		buf[t] = 0;
		t++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[t] == ';')
	{
		buf[t] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = t;
	return (1);
}

/**
 * check_chain - checks whether to continue chaining depending
 *		on last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of current location in buffer
 * @i: starting location in buffer
 * @len: actual length of buffer
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * replace_alias - replace aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 upon replacement, otherwise 0
 */
int replace_alias(info_t *info)
{
	int k;
	char *ptr;
	list_t *node;

	for (k = 0; k < 10; k++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized str
 * @info: the parameter struct
 * Return: 1 upon replacement, otherwise 0
 */
int replace_vars(info_t *info)
{
	int t = 0;
	list_t *node;

	for (t = 0; info->argv[t]; t++)
	{
		if (info->argv[t][0] != '$' || !info->argv[t][1])
			continue;

		if (!_strcmp(info->argv[t], "$?"))
		{
			replace_string(&(info->argv[t]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[t], "$$"))
		{
			replace_string(&(info->argv[t]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[t][1], '=');
		if (node)
		{
			replace_string(&(info->argv[t]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[t], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces a string
 * @old: old string address
 * @new: new string
 * Return: 1 upon replacement, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

