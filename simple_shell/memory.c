#include "shell.h"

/**
 * bfree - frees pointers & anulls the address
 * @ptr: pointer address to free
 * Return: 1 on successully freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

