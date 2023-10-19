#include "monty.h"
/**
 *rotr - swap the first and last values of the stack
 *@stack: stack of values
 *@line_number: line of instruction
 */
void rotr(stack_t **stack, unsigned int __attribute__((unused))line_number)
{
	stack_t *top = NULL, *bottom = NULL;

	if (stack == NULL || *stack == NULL)
		return;
	top = *stack, bottom = *stack;
	while (bottom->next != NULL)
		bottom = bottom->next;

	top->prev = bottom;
	bottom->next = top;
	bottom->prev->next = NULL;
	bottom->prev = NULL;
	stack[0] = bottom;
}
