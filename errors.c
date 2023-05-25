#include "shell.h"

/**
 *_eputs - prints out a string input
 * @str: the string awaiting printing
 * Return: 0
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - writes c, character, to stderr file stream
 * @c: The character awaiting printing
 * Return: 1 success, otherwise, 0, -1 incase of error
 */
int _eputchar(char c)
{
	static int j;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given file descriptor
 * @c: The character awaiting printing
 * @fd: The file descriptor to write to, destination
 * Return: 1, Successful, otherwise -1, failure or error
 */
int _putfd(char c, int file_d)
{
	static int j;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(file_d, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 *_putsfd - prints out a string input
 * @str: string awaiting printing
 * @fd: the file descriptor to write to (destination)
 * Return: total characters put
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, file_d);
	}
	return (j);
}
