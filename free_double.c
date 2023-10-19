#include "monty.h"
/**
 *free_double - free memory
 *@d: is a string
 */
void free_double(char **d)
{
	int i = 0;
	
	while (d[i] != NULL)
	{
		free(d[i]);
		i++;
	}
	free(d);
	d = NULL;
}
