#include "shell.h"

/**
 * interactive - displays, true provided shell is on interactive mode
 * @info: struct address
 * Return: 1 if on interactive mode, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks for  delimeter in characters
 * @c: the character under scrutiny
 * @delim: delimeter string
 * Return: 1 if true,otherwise 0 for false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to check from
 *Return: 1 if ccontains alphabets, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - string conversion to an integer
 *@s: the string awaiting conversion
 *Return: 0, numbers present in  string,otherwise number of conversions
 */

int _atoi(char *s)
{
	int j;
	int output;
	int sign = 1, flag = 0;
	unsigned int result = 0;

	for (j = 0;  s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result = result * 10;
			result = result + (s[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
