#include "monty.h"
/**
 *free_dlistint - free a double linked list
 *@head: double linked list
 */
void free_dlistint(stack_t *head)
{
	stack_t *tmp;

	while (head)
	{
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
