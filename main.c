#include "monty.h"
/**
 * _usage - prints usage message and exits
 *
 * Return: nothing
 */
void _usage(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}
/**
 * _error - prints file error message and exits
 * @argv: argv given by main
 *
 * Return: nothing
 */
void _error(char *argv)
{
	fprintf(stderr, "Error: Can't open file %s\n", argv);
	exit(EXIT_FAILURE);
}
/**
 * main - Entry point for the Monty interpreter.
 * @argc: Number of command line arguments.
 * @argv: Array of command line arguments.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;

	if (argc != 2 || access(argv[1], F_OK) != 0)
		_usage();

	file = fopen(argv[1], "r");
	if (!file)
		_error(argv[1]);

	if (parse_file(file, &stack) == EXIT_FAILURE)
	{
		fclose(file);
		free_stack(stack);
		return (EXIT_FAILURE);
	}
	fclose(file);
	free_stack(stack);
	return (EXIT_SUCCESS);
}

/**
 * parse_file - Parses a file line by line and executes the relevant operation.
 * @file: The file to parse.
 * @stack: The stack
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int parse_file(FILE *file, stack_t **stack)
{
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 1;
	instruction_t *instruction;
	char *opcode = NULL;

	while (getline(&line, &len, file) != -1)
	{
		opcode = strtok(line, " \t\n");

		if (!opcode || opcode[0] == '#')
		{
			line_number++;
			continue;
		}
		instruction = get_instruction(opcode);

		if (!instruction)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			free(line);
			free_stack(*stack);
			return (EXIT_FAILURE);
		}
		instruction->f(stack, line_number);
		line_number++;
	}
	free(line);
	return (EXIT_SUCCESS);
}
