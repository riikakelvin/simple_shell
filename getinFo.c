#include "shell.h"

/**
 * clear_info - clears info_t struct
 * @info: address of info_t struct
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - activates the info_t struct
 * @info: info_t struct address
 * @av: argument vect
 */
void set_info(info_t *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow1(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - free info_t struct field
 * @info: address of info_t struct
 * @all: true when all struct fields are freed
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->path = NULL;
	info->argv = NULL;

	if (all)
	{
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (!info->cmd_buff)
			free(info->arg);
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buff);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
