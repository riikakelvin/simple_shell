#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @a: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *a)
{
	int t = 0;
	unsigned long int results = 0;

	if (*a == '+')
		a++;  /* TODO: why does this make main return 255? */
	for (t = 0;  a[t] != '\0'; t++)
	{
		if (a[t] >= '0' && a[t] <= '9')
		{
			results *= 10;
			results += (a[t] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
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
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int t, icount = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		icount++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_abs_ / t)
		{
			__putchar('0' + current / t);
			icount++;
		}
		current %= t;
	}
	__putchar('0' + current);
	icount++;

	return (icount);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long no = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		no = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[no % base];
		no /= base;
	} while (no != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int t;

	for (t = 0; buf[t] != '\0'; t++)
		if (buf[t] == '#' && (!t || buf[t - 1] == ' '))
		{
			buf[t] = '\0';
			break;
		}
}
