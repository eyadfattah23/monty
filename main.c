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
	FILE *file;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: monty file\n");
		return (EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		free_stack(stack);
		return (EXIT_FAILURE);
	}


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
 * Return: A file descriptor to the opened file, or -1 on failure.
 */
FILE *open_file(char *filename)
{
	return (fopen(filename, "r"));
}
/**
 * parse_file - Parses a file line by line and executes the relevant operation.
 * @file: The file to parse.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int parse_file(FILE *file, stack_t **stack)
{
	char *line = NULL;
	ssize_t nread;
	size_t len = 0;
	unsigned int line_number = 0;
	instruction_t *instruction;
	char *opcode = NULL;

	while ((nread = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");

		if (!opcode || opcode[0] == '#')
			continue;
		instruction = get_instruction(opcode);

		if (!instruction)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			free(line);
			return (EXIT_FAILURE);
		}
		instruction->f(stack, line_number);
	}
	if (nread == -1 && !opcode)
	{
		fprintf(stderr, "Error: Failed to read file\n");
		free(line);
		return (EXIT_FAILURE);
	}
	free(line);
	return (EXIT_SUCCESS);
}
/**
 * get_next_line - get the lines in a file
 * @fd: file descriptor
 * @line: line
 * Return: -1 if failure, nread or remaining
 */

/*ssize_t get_next_line(int fd, char **line)
{
	char buff[1024], *p = buff, c;
	ssize_t remaining = 0, nread = 0;

	*line = NULL;
	while (1)
	{
		if (remaining <= 0)
		{
			remaining = read(fd, buff, 1024);
			if (remaining <= 0)
			{
				if (*line)
					return (nread);
				return (remaining);
			}
			p = buff;
		}
		c = *p++;
		remaining--;
		if (c == '\n' || c == '\0')
		{
			if (c == '\n')
				p--;
			*line = _realloc(*line, sizeof(*line), nread + p - buff + 1);
			strncat(*line, buff, p - buff);
			nread += p - buff;
			buff[0] = '\0';
			return (nread);
		}
		*line = _realloc(*line, sizeof(*line), nread + 2);
		(*line)[nread++] = c;
		(*line)[nread] = '\0';
	}
	return (-1);
}
*/
