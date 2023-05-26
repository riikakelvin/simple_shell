#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@m: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int m)
{
	int t, k;
	char *a = dest;

	t = 0;
	while (src[t] != '\0' && t < m - 1)
	{
		dest[t] = src[t];
		t++;
	}
	if (t < m)
	{
		k = t;
		while (k < m)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (a);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@m: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int m)
{
	int t, k;
	char *a = dest;

	t = 0;
	k = 0;
	while (dest[t] != '\0')
		t++;
	while (src[k] != '\0' && k < m)
	{
		dest[t] = src[k];
		t++;
		k++;
	}
	if (k < m)
		dest[t] = '\0';
	return (a);
}

/**
 **_strchr - locates a character in a string
 *@a: the string to be parsed
 *@d: the character to look for
 *Return: (a) a pointer to the memory area s
 */
char *_strchr(char *a, char d)
{
	do {
		if (*a == d)
			return (a);
	} while (*a++ != '\0');

	return (NULL);
}
