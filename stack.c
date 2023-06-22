#include "monty.h"

/**
 * push - Pushes an element to the stack.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: Line number of the instruction.
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *arg = strtok(NULL, " \t\n");
	int n;

	if (!arg || !is_number(arg))
	{
		printf("L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	n = atoi(arg);
	stack_t *new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = n;
	new_node->prev = NULL;
	if (*stack)
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
	}
	else
	{
		new_node->next = NULL;
	}
	*stack = new_node;
}

/**
 * pall - Prints all the values on the stack, starting from the top.
 * @stack: Pointer to the beginning of the stack.
 * @line_number: Line number of the instruction.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
