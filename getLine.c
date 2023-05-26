#include "shell.h"

/**
<<<<<<< HEAD
 * input_buf - puts to buffer chained commands
 * @info: parameter struct
 * @buffer: buffer address
 * @len: address of len variable
 * Return: number of bytes read
=======
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
>>>>>>> 75a5219b67ecee1a39c75f20679429daa32ee477
 */
ssize_t input_buf(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

<<<<<<< HEAD
	if (!*len)
	{
=======
	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
>>>>>>> 75a5219b67ecee1a39c75f20679429daa32ee477
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t t, k, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *o;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		k = t;
		o = buf + t;

		check_chain(info, buf, &k, t, len);
<<<<<<< HEAD
		while (k < len)
=======
		while (k < len) /* iterate to semicolon or end */
>>>>>>> 75a5219b67ecee1a39c75f20679429daa32ee477
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

<<<<<<< HEAD
		t = k + 1;
		if (t >= len)
		{
			t = len = 0;
=======
		t = k + 1; /* increment past nulled ';'' */
		if (t >= len) /* reached end of buffer? */
		{
			t = len = 0; /* reset position and length */
>>>>>>> 75a5219b67ecee1a39c75f20679429daa32ee477
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = o;
		return (_strlen(o));
	}

<<<<<<< HEAD
	*buf_p = buf;
	return (r);
=======
	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
>>>>>>> 75a5219b67ecee1a39c75f20679429daa32ee477
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @t: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *t)
{
	ssize_t r = 0;

	if (*t)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*t = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t l;
	ssize_t r = 0, a = 0;
	char *o = NULL, *new_p = NULL, *c;

	o = *ptr;
	if (o && length)
		a = *length;
	if (t == len)
		t = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + t, '\n');
	l = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(o, a, a ? a + l : l + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (o ? free(o), -1 : -1);

	if (a)
		_strncat(new_p, buf + t, l - t);
	else
		_strncpy(new_p, buf + t, l - t + 1);

	a += l - t;
	t = l;
	o = new_p;

	if (length)
		*length = a;
	*ptr = o;
	return (a);
}

/**
 * sigintHandler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
