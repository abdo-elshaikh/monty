#include "monty.h"
/**
 *main - entry point
 *@argc: number of arguments
 *@argv: arguments
 *Return: success
 */
int main(int argc, char **argv)
{
	FILE *file = NULL;
	char *line = NULL;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

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
	/*memory allocation for line before using file */
	line = malloc(sizeof(char) * 1024);
	if (line == NULL)
	{
		fprintf(stderr, "Error: Can't allocate memory for line\n");
		exit(EXIT_FAILURE);
	}
	
	while (fgets(line, sizeof(line), file) != NULL)
	{
		line_number++;
		release(&file, &line, 's');
		global.line = format_line(line);
		if (global.line == NULL || global.line[0][0] == '#' || global.line[0][0] == '\n')
		{
			free(global.line);
			continue;
		}
		get_op_function(&stack, line_number);
	}
	release(NULL, NULL, 'r');
	free_dlistint(stack);
	return (0);
}
