#include "main.h"

stack_t *stack = NULL;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;
    int found = 0;
    int i = 0;

    while ((read = getline(&line, &len, file))!= -1)
    {
        line_number++;
        char *opcode = (char *)strtok(line, "\n");
        if (opcode == NULL)
        {
            continue;
        }
        for (i = 0; instruction_t[i].opcode != NULL; i++)
        {
            if (strcmp(instruction_t[i].opcode, opcode) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            free(line);
            fclose(file);
            exit(EXIT_FAILURE);
        }

    }
    free(line);
    fclose(file);
    return (0);
}
