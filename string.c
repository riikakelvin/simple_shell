#include "shell.h"
/**
 * starts_with - checks whether needle starts with haystack
 * @haystack: the string to check
 * @needle: the substring to look for
 * Return: address of character following haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	char *retu = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (retu);
}
/**
 * _strlen - displays string length
 * @s: the string whose length is being determined
 * Return: string length
 */
int _strlen(char *s)
{
	int k = 0;

	if (!s)
		return (0);

	while (*s++)
		k++;
	return (k);
}

/**
 * _strcmp - lexicogarphically compares two strangs.
 * @s1: first string
 * @s2: second string
 * Return: negative value for s1 < s2,
 *	positive if s1 > s2,
 *	zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
