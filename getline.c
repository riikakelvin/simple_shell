#include "shell.h"

/**
 * input_buff - puts to buffer chained commands
 * @info: parameter struct
 * @buff: buffer address
 * @len: len variable address
 * Return: number of bytes read
 */
ssize_t input_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = _getline(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			{
				*len = r;
				info->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 * Return: number of bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t j, k, len;
	ssize_t r = 0;
	char **buff_ptr = &(info->arg), *ptr;

	_putchar(BUFF_FLUSH);
	r = input_buff(info, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		k = j;
		ptr = buff + j;

		check_chain(info, buff, &k, j, len);
		while (k < len)
		{
			if (is_chain(info, buff, &k))
				break;
			k++;
		}

		j = k + 1;
		if (j >= len)
		{
			j = len = 0;
			info->cmd_buff_type = CMD_NORM;
		}

		*buff_ptr = ptr;
		return (_strlen(ptr));
	}

	*buff_ptr = buff;
	return (r);
}

/**
 * read_buff - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buff(info_t *info, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buff, R_BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[R_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buff(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: signal number
 * Return: 0
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$  ");
	_putchar(BUFF_FLUSH);
}
