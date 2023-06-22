#include "monty.h"

/**
 * nop - Does nothing.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: Line number of the instruction.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * get_instruction - Searches for an instruction based on opcode.
 * @opcode: Opcode to search for.
 *
 * Return: Pointer to the instruction struct if found, NULL otherwise.
 */
instruction_t *get_instruction(char *opcode)
{
	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL}
	};

	int i = 0;

	while (instructions[i].opcode)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
			return (&instructions[i]);
		i++;
	}

	return (NULL);
}

/**
 * free_stack - Frees a stack_t stack.
 * @stack: Pointer to the beginning of the stack.
 */
void free_stack(stack_t *stack)
{
	stack_t *temp;

	while (stack)
	{
		temp = stack;
		stack = stack->next;
		free(temp);
	}
}
/**
 * is_number - Checks if a string is a number.
 * @str: The string to check.
 *
 * Return: 1 if the string is a number, 0 otherwise.
 */
int is_number(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
