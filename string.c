#include "shell.h"

/**
 * _strlen - displays string length
 * @s: the string under consideration
 * Return: value of the lengh of string
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - lexicogarphically compares two strings
 * @s1: the first string under cosnideration
 * @s2: the second string under consideration
 * Return: negative value if s1 < s2,
 *	positive value when s1 > s2,
 *	zero when s1 equates to s2
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

/**
 * starts_with - checks whether needle starts with haystack
 * @haystack: string to search through
 * @needle: the sub string the program is looking for
 * Return:  next char address of haystack, otherwise Null
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
 * @dest: destination
 * @src: source
 * Return: pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
