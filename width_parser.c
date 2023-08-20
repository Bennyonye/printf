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
		if (is_digit(format[curr_i])) // Check if character is a digit
		{
			width = (width * 10) + (format[curr_i] - '0'); // Update the width
		}
		else if (format[curr_i] == '*') // Check if width is specified in the argument list
		{
			width = va_arg(list, int);
			break;
		}
		else
		{
			break; // Exit loop if neither a digit nor '*'
		}
	}

	*i = curr_i - 1; // Update the index

	return width;
}

