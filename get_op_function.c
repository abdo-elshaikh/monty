#include "monty.h"
/**
 *get_op_function - execute the monty instructions
 *@stack: pointer to the top of the stack
 *@line_number: line number
 *Return: nothing
 */
void get_op_function(stack_t **stack, unsigned int line_number)
{
	instruction_t instruction[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"div", _div},
		{"mul", mul},
		{"mod", mod},
		{"swap", swap},
		{"rotl", rotl},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotr", rotr},
		{NULL, NULL}};
	int i;
	int unknown_opcode = 1;

	for (i = 0; instruction[i].opcode != NULL; i++)
	{
		if (strcmp(instruction[i].opcode, global.line[0]) == 0)
		{
			instruction[i].f(stack, line_number);
			unknown_opcode = 0;
			break;
		}
	}
	if (unknown_opcode)
	{
		fprintf(stderr, "L%u: unknown instruction %s\n",
				line_number, global.line[0]);
		release(NULL, NULL, 'r');
		free(global.line);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
}
