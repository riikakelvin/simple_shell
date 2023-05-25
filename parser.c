#include "shell.h"

/**
 * dup_chars - duplicates characters
 * @pathstr: the string path
 * @start: start duplicating index
 * @stop: stop duplicating index
 * Return: the pointer to the new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buff[l++] = pathstr[j];
	buff[l] = 0;
	return (buff);
}

/**
 * find_path - finds specific cmd from the string path
 * @info: the parameter struct
 * @pathstr: the string path
 * @cmd: the specific cmd to find
 * Return: full path of cmd when found,otherwise NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}

/**
 * is_cmd - determines whether a file is an executable command
 * @info: the struct parameter
 * @path: actual path to the file location
 * Return: 1 if true, otherwise 0 for false
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
