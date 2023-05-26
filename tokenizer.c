#include "shell.h"

/**
 * **strtow - splits a string to words
 * @str: input string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL for failure
 */

char **strtow(char *str, char *d)
{
	int t, a, k, r num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (t = 0; str[t] != '\0'; t++)
		if (!is_delim(str[t], d) && (is_delim(str[t + 1], d) || !str[t + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (t = 0, a = 0; a < num_words; a++)
	{
		while (is_delim(str[t], d))
			t++;
		k = 0;
		while (!is_delim(str[t + k], d) && str[t + k])
			k++;
		s[a] = malloc((k + 1) * sizeof(char));
		if (!s[a])
		{
			for (k = 0; k < a; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < k; r++)
			s[a][r] = str[t++];
		s[a][t] = 0;
	}
	s[a] = NULL;
	return (s);
}

/**
 * **strtow2 - splits string to words
 * @str: input string
 * @d: delimeter
 * Return: a pointer to an array of strings, otherwise NULL
 */
char **strtow2(char *str, char d)
{
	int t, a, k, r, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (t = 0; str[t] != '\0'; t++)
		if ((str[t] != d && str[t + 1] == d||
					(str[t] != d && !str[t + 1]) ||
					str[t + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (t = 0, a = 0; a < num_words; a++)
	{
		while (str[t] == d && str[t] != d)
			t++;
		k = 0;
		while (str[t + k] != d && str[t + k] && str[t + k] != d)
			k++;
		s[a] = malloc((k + 1) * sizeof(char));
		if (!s[a])
		{
			for (k = 0; k < a; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (r = 0; r < k; r++)
			s[a][r] = str[t++];
		s[a][r] = 0;
	}
	s[a] = NULL;
	return (s);
}
