#include "shell.h"
/**
 * _strdup - duplicates strings
 * @str: string to duplicate
 * Return: pointer to the duplicated string(outcome)
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *retu;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	retu = malloc(sizeof(char) * (len + 1));
	if (!retu)
		return (NULL);
	for (len++; len--;)
		retu[len] = *--str;
	return (retu);
}
/**
 * _strcpy - copies strings
 * @dest: to copy to
 * @src: to copy from
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int t = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[t])
	{
		dest[t] = src[t];
		t++;
	}
	dest[t] = 0;
	return (dest);
}

/**
 * _puts - prints input string
 * @str: the string awaiting printing
 * Return: void
 */
void _puts(char *str)
{
	int tk = 0;

	if (!str)
		return;
	while (str[tk] != '\0')
	{
		_putchar(str[tk]);
		tk++;
	}
}

/**
 * _putchar - writes character c to standad output
 * @c: The character awaiting print
 * Return: Succesful 1, otherwise -1 for error
 */
int _putchar(char c)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(1, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

