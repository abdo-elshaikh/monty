#include "monty.h"
/**
 *format_line - prepare the monty instructions for execution
 *@input: raw monty instruction
 *Return: instructions formated or null in failure
 */
char **format_line(char *input)
{
	char **tokens = NULL;
	char *token = NULL;
	size_t tokenCount = 0;

	if (input == NULL || input[0] == '\0')
		return (NULL);

	delete_newline(&input);

	if (empty_codes(&input) == 1)
		return ('\0');

	tokens = malloc(sizeof(char **) * 3);
	if (tokens == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		release(NULL, NULL, 'r');
		exit(EXIT_FAILURE);
	}

	tokens[0] = NULL;
	tokens[1] = NULL;
	tokens[2] = NULL;

	token = strtok(input, " ");
	while (token != NULL && tokenCount <= 1)
	{
		tokens[tokenCount] = token;
		token = strtok(NULL, " ");
		if (tokenCount >= 1)
			break;
		tokenCount++;
	}

	tokens[tokenCount + 1] = NULL;
	return (tokens);
}
