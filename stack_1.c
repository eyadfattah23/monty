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
	instruction_t *instructions = malloc(sizeof(instruction_t) * 7);
	int i;

	instructions[0].opcode = "push";
	instructions[0].f = push;
	instructions[1].opcode = "pall";
	instructions[1].f = pall;
	instructions[2].opcode = "pint";
	instructions[2].f = pint;
	instructions[3].opcode = "pop";
	instructions[3].f = pop;
	instructions[4].opcode = "swap";
	instructions[4].f = swap;
	instructions[5].opcode = "nop";
	instructions[5].f = nop;
	instructions[6].opcode = NULL;
	instructions[6].f = NULL;
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
 * is_digit - checks if a string is a digit
 * @string: string to check
 *
 * Return: 1 if success, 0 if not
 */
int is_digit(char *string)
{
	if (!string || *string == '\0')
		return (0);
	if (*string == '-')
		string++;
	while (*string)
	{
		if (isdigit(*string) == 0)
			return (0);
		string++;
	}
	return (1);
}
/**
 * is_number - Checks if a string is a number.
 * @str: The string to check.
 *
 * Return: 1 if the string is a number, 0 otherwise.
 */
int is_number(char *str)
{
	int i;

	if (!str)
		return (0);

	for (i = 0; str[i]; i++)
		if (i < '0' || i > '9')
			return (0);

	return (1);
}
