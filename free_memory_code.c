#include "shell.h"

/**
 * bfree - frees pointers and anulls their address
 * @ptr: pointer address to be freed
 * Return: 1 successfully freed, otherwise 0.
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
