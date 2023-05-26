#include "shell.h"

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to a prev memory allocated block
 * @old_size: size in bytes of the prev memory block
 * @new_size: size in bytes of the new memory block
 * Return: pointer to the old mem block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pi;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pi = malloc(new_size);
	if (!pi)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pi[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pi);
}
/**
 * ffree - frees a string from strings
 * @pp: string from strings
 */
void ffree(char **pp)
{
	char **k = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(k);
}
/**
 * _memset - sets memory with a specified byte size
 * @s: a pointer to the memory section
 * @b: the size of byte to set memory pointer with
 * @n: size of bytes to be set
 * Return: s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int t;

	for (t = 0; t < n; t++)
		s[t] = b;
	return (s);
}

