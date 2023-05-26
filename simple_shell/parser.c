#include "shell.h"

/**
 * find_path - searches this cmd in string path
 * @info: the info struct
 * @pathstr: the string path
 * @cmd: the cmd to being searched
 * Return: full path of cmd when found, otherwise Null
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int t = 0, curr_post = 0;
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
		if (!pathstr[t] || pathstr[t] == ':')
		{
			path = dup_chars(pathstr, curr_post, t);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[t])
				break;
			curr_post = t;
		}
		t++;
	}
	return (NULL);
}
/**
 * is_cmd - determines whether file is an executable cmd
 * @info: the info struct
 * @path: full path to the file
 * Return: 1 when true, otherwise 0 for false (boolean)
 */
int is_cmd(info_t *info, char *path)
{
	struct stat sti;

	(void)info;
	if (!path || stat(path, &sti))
		return (0);

	if (sti.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicate characters
 * @pathstr: the string path
 * @start: start index
 * @stop: stop index
 * Return: pointer to newly made (on duplicate) buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int t = 0, k = 0;

	for (k = 0, t = start; t < stop; t++)
		if (pathstr[t] != ':')
			buf[k++] = pathstr[t];
	buf[k] = 0;
	return (buf);
}

