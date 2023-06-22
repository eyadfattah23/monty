#include "monty.h"

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to memory block
 * @old_size: size of old memory block
 * @new_size: size of new memory block
 * Return: pointer to new memory block
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
 * append_node - append a node to the start of a stack_t stack
 * @stack: stack head
 * @n: new node number
 *
 * Return: newly created node, if creation fails, the
 * function will return NULL.
 */
stack_t *append_node(stack_t **stack, const int n)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(new_node);
		return (NULL);
	}
	new_node->n = n;

	new_node->next = *stack;
	new_node->prev = NULL;
	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;

	return (new_node);
}
