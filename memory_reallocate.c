#include "shell.h"

/**
 **_memset - allocates memory with a specified byte size
 *@s: pointer to the memory block
 *@b: the byte to fill s pointer with
 *@n: the require bytes size to fill with
 *Return: pointer to s memory block
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - frees a string from a set of strings
 * @pp: a singular string from strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to prev memory allocated block
 * @old_size: previous block size of bytes
 * @new_size: new block size of bytes
 * Return: pointer to prev block addres
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
