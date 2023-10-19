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
	char *monty_codes = NULL;
	size_t size = 0;
	unsigned int n_line = 0;
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
	while (getline(&monty_codes, &size, file) != -1)
	{
		n_line++;
		release(&file, &monty_codes, 's');
		if (n_line == 1)
			continue;
		global.line = format_line(monty_codes);
		if (global.line == NULL || global.line[0] == NULL || global.line[0][0] == '#')
			continue;
		else
			get_op_function(&stack, n_line);

	}
	release(NULL, NULL, 'r');
	free_double(global.line);
	free_dlistint(stack);
	return (0);
}
