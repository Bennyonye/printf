#include "main.h"

/**
 * width_parser - Calculates the width for printing.
 * @format: Formatted string in which to print the arguments.
 * @i: Index within the format string.
 * @list: List of arguments to retrieve width if specified as '*'.
 *
 * Return: Width value for printing.
 */
int width_parser(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		/* Check if character is a digit */
		if (is_digit(format[curr_i]))
		{
			/* Update the width */
			width = (width * 10) + (format[curr_i] - '0');
		}
		/* Check if width is specified in the argument list */
		else if (format[curr_i] == '*')
		{
			width = va_arg(list, int);
			break;
		}
		else
		{
			/* Exit loop if neither a digit nor '*' */
			break;
		}
	}

	/* Update the index */
	*i = curr_i - 1;

	return width;
}
