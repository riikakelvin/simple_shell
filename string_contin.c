#include "shell.h"

/**
 * _strcpy - copies strings
 * @dest: destination to be copied
 * @src: source of string
 * Return: pointer to destination copied
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicates strings
 * @str: the string awaiting duplication
 * Return: pointer to the duplicated string output
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 * _puts - prints input strings
 * @str: the string awaiting printing
 * Return: 0
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - writes c to the standard output
 * @c: character awaiting printing
 * Return: O1 successful, otherwise -1
 */
int _putchar(char c)
{
	static int j;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (c != BUFF_FLUSH)
		buff[j++] = c;
	return (1);
}

