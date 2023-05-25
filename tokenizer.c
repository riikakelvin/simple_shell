#include "shell.h"

/**
 * **strtow1 - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow1(char *str, char *d)
{
	int j, k, l, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (j = 0; str[j] != '\0'; j++)
		if (!is_delim(str[j], d) && (is_delim(str[j + 1], d) || !str[j + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);

	for (j = 0, k = 0; k < num_words; k++)
	{
		while (is_delim(str[j], d))
			j++;
		k = 0;
		while (!is_delim(str[j + l], d) && str[j + l])
			l++;
		s[k] = malloc((l + 1) * sizeof(char));
		if (!s[k])
		{
			for (l = 0; l < k; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			s[k][m] = str[j++];
		s[k][m] = 0;
	}
	s[k] = NULL;
	return (s);
}

/**
 * **strtow2 - splits strings into words
 * @str: input string
 * @d: delimeter
 * Return: a pointer to an array of strings (succes), or NULL for failure
 */
char **strtow2(char *str, char d)
{
	int j, k, l, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (j = 0; str[j] != '\0'; j++)
		if ((str[j] != d && str[j + 1] == d) ||
				    (str[j] != d && !str[j + 1]) || str[j + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, k = 0; k < num_words; k++)
	{
		while (str[j] == d && str[j] != d)
			j++;
		l = 0;
		while (str[j + l] != d && str[j + l] && str[j + l] != d)
			l++;
		s[k] = malloc((l + 1) * sizeof(char));
		if (!s[k])
		{
			for (l = 0; l < j; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			s[k][m] = str[j++];
		s[k][m] = 0;
	}
	s[k] = NULL;
	return (s);
}
