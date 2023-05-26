#include "shell.h"

/**
 * _eputs - prints an input string
 * @string: string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
	int t = 0;

	if (!string)
		return;
	while (string[t] != '\0')
	{
		_eputchar(string[t]);
		t++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @d: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char d)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(2, buf, t);
		t = 0;
	}
	if (d != BUF_FLUSH)
		buf[t++] = d;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @d: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char d, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(fd, buf, t);
		t = 0;
	}
	if (d != BUF_FLUSH)
		buf[t++] = d;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @string: string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *string, int fd)
{
	int t = 0;

	if (!string)
		return (0);
	while (*string)
	{
		t += _putfd(*string++, fd);
	}
	return (t);
}
