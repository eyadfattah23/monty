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
		fprintf(stderr, "Usage: monty file\n");
		return (EXIT_FAILURE);
	}
	int file = open_file(argv[1]);

	if (file == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	stack_t *stack = NULL;

	if (parse_file(file, &stack) == EXIT_FAILURE)
	{
		close(file);
		free_stack(stack);
		return (EXIT_FAILURE);
	}
	close(file);
	free_stack(stack);
	return (EXIT_SUCCESS);
}

/**
 * open_file - Opens the file specified by filename.
 * @filename: The name of the file to open.
 *
 * Return: A file descriptor to the opened file, or -1 on failure.
 */
int open_file(char *filename)
{
    return open(filename, O_RDONLY);
}
/**
 * parse_file - Parses a file line by line and executes the relevant operation.
 * @file: The file to parse.
 * @stack: A pointer to the stack.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int parse_file(int file, stack_t **stack)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	unsigned int line_number = 0;

	while ((nread = get_next_line(file, &line)) > 0)
	{
		line_number++;
		char *opcode = strtok(line, " \t\n");

		if (!opcode || opcode[0] == '#')
			continue;
		instruction_t *instruction = get_instruction(opcode);

		if (!instruction)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			free(line);
			return (EXIT_FAILURE);
		}
		instruction->f(stack, line_number);
	}
	if (nread == -1)
	{
		fprintf(stderr, "Error: Failed to read file\n");
		free(line);
		return (EXIT_FAILURE);
	}
	free(line);
	return (EXIT_SUCCESS);
}
