#include "monty.h"
/**
 *rotl - get the top element to bottom
 *@stack: stack elements
 *@line_number: number of instructions
 */
void rotl(stack_t **stack, unsigned int __attribute__((unused))line_number)
{
	stack_t *top, *bottom;

	if (stack == NULL || *stack == NULL)
		return;
	top = *stack, bottom = *stack;
	while (bottom->next != NULL)
		bottom = bottom->next;
	bottom->next = top;
	top->prev = bottom;
	top->next->prev = NULL;
	*stack = top->next;
	top->next = NULL;
}
