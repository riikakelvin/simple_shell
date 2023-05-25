#include "shell.h"

/**
 * _myenv - displays current environment
 * @info: contains potential arguments to maintain  function prototype.
 * Return: Always 0 (success)
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - obtains value of an environment variable
 * @info: contains potential arguments to maintain function prototype.
 * @name:  name of envitonment variable
 * Return: the value obtained
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - newly sets an environment variable, or modifies it
 * @info: contains potential arguments to maintain function prototype.
 *  Return: Always 0 (sucessful)
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements displayed\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Deletes an environment variable
 * @info: contains potential arguments to maintain function prototype.
 *  Return: Always 0 (successful)
 */
int _myunsetenv(info_t *info)
{
	int ind;

	if (info->argc == 1)
	{
		_eputs("Arguements. are Too Few\n");
		return (1);
	}
	for (ind = 1; ind <= info->argc; ind++)
		_unsetenv(info, info->argv[ind]);

	return (0);
}

/**
 * populate_env_list - generates list linked to environment
 * @info: contains potential arguments to maintain function prototype.
 * Return: Always 0 (successful)
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t ind;

	for (ind = 0; environ[ind]; ind++)
		add_the_node_end(&node, environ[ind], 0);
	info->env = node;
	return (0);
}
