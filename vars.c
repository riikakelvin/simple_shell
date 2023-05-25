#include "shell.h"

/**
 * is_chain - tests whether current chars in buffer are a chain delimeter
 * @info: struct parameter
 * @buff: characters buffer
 * @p: address of current location in the bufffer
 * Return: 1 for chain delimeter, otherwise 0
 */
int is_chain(info_t *info, char *buff, size_t *p)
{
	size_t k = *p;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[k] == '&' && buf[k + 1] == '&')
	{
		buff[k] = 0;
		k++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[k] == ';')
	{
		buff[k] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * replace_string - replaces a string with new one
 * @old: address of the  initial string
 * @new: new string replacement
 * Return: 1 incase of replacement, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_alias - replace aliases in tokenized strs
 * @info: the struct parameter
 * Return: 1 in case of replacement,otherwise 0
 */
int replace_alias(info_t *info)
{
	int j;
	list_t *node;
	char *p;

	for (j = 0; j < 10; j++)
	{
		node = node_to_start_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in tokenized strs
 * @info: the struct parameter
 * Return: 1 incase of replacement, otherwise 0
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_to_start_with(info->env, &info->argv[j][1], '=');
		if (node)
		{
			replace_string(&(info->argv[j]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}
/**
 * check_chain - continues checking chaining based on last status
 * @info: the struct parameter
 * @buff: character buffer
 * @p: address of current locationn in buffer
 * @i: starting position in buffer
 * @len: actual length of the buffer
 * Return: 0
 */
void check_chain(info_t *info, char *buff, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			k = len;
		}
	}
	*p = k;
}
