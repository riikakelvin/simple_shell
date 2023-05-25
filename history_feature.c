#include "shell.h"

/**
 * get_history_file - obtains the history file
 * @info: the struct parameter
 * Return: the string that contains the history file obtained
 */

char *get_history_file(info_t *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - writes a file, or modifies an existing one
 * @info: the struct parameter
 * Return: 1 (successful), otherwise -1, Failure
 */
int write_history(info_t *info)
{
	ssize_t file_d;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	{
		free(filename);
	}
	if (file_d == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file_d);
		_putfd('\n', file_d);
	}
	_putfd(BUFF_FLUSH, file_d);
	close(file_d);
	return (1);
}

/**
 * read_history - reads history from a file
 * @info: the struct parameter
 * Return: histcounst (successful, otherwise, 0
 */
int read_history(info_t *info)
{
	int j, last = 0, linecount = 0;
	ssize_t file_d, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	file_d = open(filename, O_RDONLY);
	{
		free(filename);
	}
	if (file_d == -1)
		return (0);
	if (!fstat(file_d, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(file_d, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(file_d);
	for (j = 0; j < fsize; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			build_history_list(info, buff + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, buff + last, linecount++);
	{
		free(buff);
	}
	info->histcount = linecount;
	while (info->histcount-- >= MAX_HIST)

	delete_the_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds more provision to a history linked list
 * @info: Contains potential arguments for maintenance of specific prototype
 * @buff: buffer
 * @linecount: the history linecount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_the_node_end(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history linked list after changes are effected
 * @info: Contains potential arguments for maintenance of specific prototype;
 * Return: new histcount (Success)
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
