#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delims - checks if character is a delimeter
 * @d: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delims(char d, char *delims)
{
	while (*delims)
		if (*delims++ == d)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic characters
 * @d: The letter to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts string to integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int t, sgn = 1, flag = 0, out;
	unsigned int results = 0;

	for (t = 0; s[t] != '\0' && flag != 2; t++)
	{
		if (s[t] == '-')
			sgn *= -1;

		if (s[t] >= '0' && s[t] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (s[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sgn == -1)
		out = -results;
	else
		out = results;

	return (out);
}
