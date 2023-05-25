#include "shell.h"

/**
 * _erratoi - conversion of strings to integers
 * @s: the string awaiting conversion
 * Return: 0 no integers in string,  otherwise -1 failure
 */
int _erratoi(char *s)
{
	int j = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			result = result * 10;
			result = result + (s[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints out an error message
 * @info: the parameter & return info struct
 * @estr: string that contains the specified error
 * Return: 0 no integers in string, -1 for error, otherwise conversion success
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints out decimal numbers to base 10
 * @input: the input
 * @fd: the filedescriptor to write to (destination)
 * Return: the number of characters that are printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j = 0;
	int count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current = current % j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - an itoa clone, duplicate
 * @num: numbers
 * @base: the base value
 * @flags: argument flags to use
 * Return: a string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces initial instance of '#' with null terminator
 * @buff: string address awaiting modification
 * Return: Always 0, success
 */
void remove_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
