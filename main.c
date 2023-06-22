#include "monty.h"

/**
 * main - Entry point for the Monty interpreter.
 * @argc: Number of command line arguments.
 * @argv: Array of command line arguments.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: monty file\n");
		return (EXIT_FAILURE);
	}
	FILE *file = open_file(argv[1]);

	if (!file)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	stack_t *stack = NULL;

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
 * open_file - Opens the file specified by filename.
 * @filename: The name of the file to open.
 *
 * Return: A FILE pointer to the opened file, or NULL on failure.
 */
FILE *open_file(char *filename)
{
	return (fopen(filename, "r"));
}

/**
 * parse_file - Parses a file line by line and executes the relevant operation.
 * @file: The file to parse.
 * @stack: A pointer to the stack.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int parse_file(FILE *file, stack_t **stack)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	unsigned int line_number = 0;

	while ((nread = getline(&line, &len, file)) != -1)
	{
		line_number++;
		char *opcode = strtok(line, " \t\n");

		if (!opcode || opcode[0] == '#')
			continue;
		instruction_t *instruction = get_instruction(opcode);

		if (!instruction)
		{
			printf("L%d: unknown instruction %s\n", line_number, opcode);
			free(line);
			return (EXIT_FAILURE);
		}
		instruction->f(stack, line_number);
	}
	free(line);
	return (EXIT_SUCCESS);
}
