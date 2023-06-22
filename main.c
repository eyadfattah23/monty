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
	int file = open(argv[1], O_RDONLY);
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: monty file\n");
		return (EXIT_FAILURE);
	}

	if (file == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	if (parse_file(file) == EXIT_FAILURE)
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
int parse_file(int file)
{
	char *line = NULL;
	ssize_t nread;
	unsigned int line_number = 0;
	int instruction;
	char *opcode = NULL;

	nread = get_next_line(file, &line);
	while (nread > 0)
	{
		line_number++;
		opcode = strtok(line, " \t\n");

		if (!opcode || opcode[0] == '#')
			continue;
		instruction = get_instruction(opcode, line_number);

		if (!instruction)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			free(line);
			return (EXIT_FAILURE);
		}
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

ssize_t get_next_line(int fd, char **line)
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
}
