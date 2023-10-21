#include "monty.h"
global_t global;
/**
 * main - check the code
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: Always 0
*/
int main(int argc, char **argv)
{
	stack_t *stack_ptr = NULL;
	FILE *file;
	char current_line[100];
	unsigned int current_line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(current_line, sizeof(current_line), file) != NULL)
	{
		current_line_number++;
		global.line = format_line(current_line);
		if (global.line == NULL || global.line[0][0] == '#')
		{
			continue;
		}
		get_op_function(&stack_ptr, current_line_number);
	}
	fclose(file);

	return (0);
}
