#include "shell.h"

/**
 **_strncpy - copy strings
 *@dest: the destination a string to be copied
 *@src: the source string being copied
 *@n: number of characters being copied
 *Return: string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, k;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		k = j;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: number of bytes effectively used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int j, k;
	char *str = dest;

	k = 0;
	j = 0;
	while (dest[j] != '\0')
		j++;
	while (src[k] != '\0' && k < n)
	{
		dest[j] = src[k];
		j++;
		k++;
	}
	if (k < n)
		dest[j] = '\0';
	return (str);
}

/**
 **_strchr -finds a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (*s)
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
