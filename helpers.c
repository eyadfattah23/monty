#include "monty.h"

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to memory block
 * @old_size: size of old memory block
 * @new_size: size of new memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *old_ptr;
	int m, i;

	if (new_size <= old_size)
	{
		m = new_size;
	} else
	{
		m = old_size;
	}
	if (new_size == old_size)
	{
		return (ptr);
	}
	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	if (!new_ptr)
	{
		return (NULL);
	}
	old_ptr = ptr;
	for (i = 0; i < m; i++)
	{
		new_ptr[i] = old_ptr[i];
	}
	free(ptr);
	return (new_ptr);
}

/**
 * is_integer - checks if a string represents an integer
 * @input: the string to check
 *
 * Return: true if the string represents an integer, false otherwise
 */
int is_integer(char *input)
{
	long int num = 0;
	int negative;

	if (*input == '\0')
		return (0);

	negative = (*input == '-');
	if (negative || *input == '+')
		input++;

	while (*input != '\0')
	{
		if (*input < '0' || *input > '9')
			return (0);

		num = num * 10 + (*input - '0');
		input++;
	}

	if (negative)
		num *= -1;

	return (1);
}
