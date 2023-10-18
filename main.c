#include "main.h"

stack_t *stack = NULL;
int queue_mode = 0;

/*main.c:*/

/**
 * main - check the code
 * @argc: the number of arguments
 * @argv: the array of arguments
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
    char *line = NULL;
    unsigned int line_number = 0;
    int found = 0;
    int i;
    FILE *file;
    char *opcode;

    instruction_t opcodes[] = {
        {"push", _push},
        {"pall", _pall},
        {"pint", _pint},
        {"pop", _pop},
        {"add", _add},
        {"sub", _sub},
        {"mul", _mul},
        {"div", _div},
        {"mod", _mod},
        {"pchar", _pchar},
        {"pstr", _pstr},
        {"rotl", _rotl},
        {"rotr", _rotr},
        {"nop", _nop},
        {"swap", _swap},
        {"stack", _stack},
        {"queue", _queue},
        {"neg", _neg},
    };

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
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;
        opcode = strtok(line, " \n\t");

        if (!opcode)
            continue;
        if (opcode[0] == '#')
            continue;
        for (i = 0; i < 13; i++)
        {
            if (strcmp(opcode, opcodes[i].opcode) == 0)
            {
                opcodes[i].f(&stack, line_number);
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
        found = 0;
    }
    free(line);
    free_stack(&stack);
    fclose(file);
    return 0;
}

/**
 * free_stack - Frees all elements of the stack.
 * @stack: The stack to free.
 * Return: Nothing
 */
void free_stack(stack_t **stack)
{
    stack_t *current = *stack;
    while (current)
    {
        stack_t *temp = current;
        current = current->next;
        free(temp);
    }
    *stack = NULL;
}

/**
 * _is_integer - Checks if a string is an integer.
 * @str: The string to check.
 * Return: 1 if the string is an integer, 0 otherwise.
 */
int _is_integer(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}
/**
 * push - Pushes an element to the stack.
 * @stack: The stack to push to.
 * @line_number: The line number of the push instruction.
 * Return: Nothing
 */
void _push(stack_t **stack, unsigned int line_number)
{
    char *arg = strtok(NULL, " \n\t");
    stack_t *new_node = NULL;
    if (arg == NULL || !_is_integer(arg))
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }
    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = atoi(arg);
    new_node->prev = NULL;
    new_node->next = *stack;
    if (*stack)
        (*stack)->prev = new_node;
    *stack = new_node;
}

/**
 * pall - Prints all elements of the stack.
 * @stack: The stack to print.
 * @line_number: The line number of the pall instruction.
 * Return: Nothing
 */
void _pall(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    temp = *stack;
    (void)line_number;
    while (temp)
    {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}

/**
 * pint - Prints the value at the top of the stack.
 * @stack: The stack to print.
 * @line_number: The line number of the pint instruction.
 * Return: Nothing
 */
void _pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }
    printf("%d\n", (*stack)->n);
}

/**
 * pop - Removes the top element of the stack.
 * @stack: The stack to pop from.
 * @line_number: The line number of the pop instruction.
 * Return: Nothing
 */
void _pop(stack_t **stack, unsigned int line_number)
{
    stack_t *temp = NULL;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }
    temp = *stack;
    *stack = temp->next;
    if (*stack)
        (*stack)->prev = NULL;
    free(temp);
}

/**
 * swap - Swaps the top two elements of the stack.
 * @stack: The stack to swap.
 * @line_number: The line number of the swap instruction.
 * Return: Nothing
 */
void _swap(stack_t **stack, unsigned int line_number)
{
    int temp = 0;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    temp = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
}

/**
 * add - Adds the top two elements of the stack.
 * @stack: The stack to add.
 * @line_number: The line number of the add instruction.
 * Return: Nothing
 */
void _add(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    (*stack)->next->n += (*stack)->n;
    _pop(stack, line_number);
}

/**
 * sub - Subtracts the top two elements of the stack.
 * @stack: The stack to subtract.
 * @line_number: The line number of the sub instruction.
 * Return: Nothing
 */
void _sub(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    (*stack)->next->n -= (*stack)->n;
    _pop(stack, line_number);
}

/**
 * div - Divides the top two elements of the stack.
 * @stack: The stack to divide.
 * @line_number: The line number of the div instruction.
 * Return: Nothing
 */
void _div(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }
    (*stack)->next->n /= (*stack)->n;
    _pop(stack, line_number);
}

/**
 * mul - Multiplies the top two elements of the stack.
 * @stack: The stack to multiply.
 * @line_number: The line number of the mul instruction.
 * Return: Nothing
 */
void _mul(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    (*stack)->next->n *= (*stack)->n;
    _pop(stack, line_number);
}

/**
 * mod - Modifies the top element of the stack.
 * @stack: The stack to modify.
 * @line_number: The line number of the mod instruction.
 * Return: Nothing
 */
void _mod(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }
    (*stack)->next->n %= (*stack)->n;
    _pop(stack, line_number);
}

/**
 * pstr - Prints the string stored in the top element of the stack.
 * @stack: The stack to print.
 * @line_number: The line number of the pstr instruction.
 * Return: Nothing
 */
void _pstr(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pstr, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    printf("%d\n", (*stack)->n);
}

/**
 * rotl - Rotates the stack to the left.
 * @stack: The stack to rotate.
 * @line_number: The line number of the rotl instruction.
 * Return: Nothing
 */
void _rotl(stack_t **stack, unsigned int line_number)
{
    stack_t *first = NULL;
    stack_t *second = NULL;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't rotl, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    first = *stack;
    second = (*stack)->next;
    *stack = (*stack)->next;
    first->next = NULL;
    first->prev = second;
    second->next = first;
}

/**
 * rotr - Rotates the stack to the right.
 * @stack: The stack to rotate.
 * @line_number: The line number of the rotr instruction.
 * Return: Nothing
 */
void _rotr(stack_t **stack, unsigned int line_number)
{
    stack_t *first = NULL;
    stack_t *last = NULL;

    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't rotr, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    first = *stack;
    last = *stack;
    while (last->next != NULL)
        last = last->next;
    *stack = last;
    last->next = first;
    first->prev = last;
    first->next = NULL;
    last->prev = NULL;
}

/**
 * pchar - Prints the character stored in the top element of the stack.
 * @stack: The stack to print.
 * @line_number: The line number of the pchar instruction.
 * Return: Nothing
 */
void _pchar(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }
    if (!isprint((*stack)->n))
    {
        fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
        exit(EXIT_FAILURE);
    }
    printf("%c\n", (*stack)->n);
}

/**
 * nop - Does nothing.
 * @stack: The stack to nop.
 * @line_number: The line number of the nop instruction.
 * Return: Nothing
 */
void _nop(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
}

/**
 * neg - Negates the top element of the stack.
 * @stack: The stack to negate.
 * @line_number: The line number of the neg instruction.
 * Return: Nothing
 */
void _neg(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't neg, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }
    (*stack)->n *= -1;
}
/**
 * stack - Prints the stack.
 * @stack: The stack to print.
 * @line_number: The line number of the stack instruction.
 * Return: Nothing
 */
void _stack(stack_t **stack, unsigned int line_number)
{
    queue_mode = 0;
    (void)stack;
    (void)line_number;
}
/**
 * queue - Prints the queue.
 * @stack: The stack to print.
 * @line_number: The line number of the queue instruction.
 * Return: Nothing
 */
void _queue(stack_t **stack, unsigned int line_number)
{
    queue_mode = 1;
    (void)stack;
    (void)line_number;
}