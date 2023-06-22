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
	instruction_t *instructions = malloc(sizeof(instruction_t) * 8);
	int i;

	instructions[0] = (instruction_t){"push", push};
	instructions[1] = (instruction_t){"pall", pall};
	instructions[2] = (instruction_t){"pint", pint};
	instructions[3] = (instruction_t){"pop", pop};
	instructions[4] = (instruction_t){"swap", swap};
	instructions[5] = (instruction_t){"add", add};
	instructions[6] = (instruction_t){"nop", nop};
	instructions[7] = (instruction_t){NULL, NULL};
	i = 0;
	while (instructions[i].opcode)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
			return (&instructions[i]);
		i++;
	}

	free(instructions);
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
