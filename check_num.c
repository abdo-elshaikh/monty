#include "monty.h"
/**
 *check_num - check if the string is a number
 *@number: string
 *Return: 1 if its a number, -1 if its dont
 */
int check_num(char *number)
{
	int i = 0;

	while (number[i] != '\0')
	{
		if (number[i] < '0' || number[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}
