#include "monty.h"
/**
 *swap - swap the first two elements of the stack
 *@stack: stack
 *@last_line: number line isntruction
 */
void swap(stack_t **stack, unsigned int last_line)
{
	stack_t *top_rear, *rear_top;

	if (stack[0] == NULL || stack[0]->next == NULL)
	{
		fprintf(stderr, "L%i: can't swap, stack too short\n", last_line);
		exit(EXIT_FAILURE);
	}
	top_rear = stack[0];
	rear_top = stack[0]->next;
	if (top_rear->next->next != NULL)
	{
		top_rear->next = rear_top->next;
		rear_top->next->prev = top_rear;
	}
	else
		top_rear->next = NULL;
	top_rear->prev = rear_top;

	rear_top->next = top_rear;
	rear_top->prev = NULL;
	*stack = rear_top;
}
