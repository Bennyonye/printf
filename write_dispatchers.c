#include "main.h"

/************************* HANDLE WRITE FOR CHARACTERS *************************/
/**
 * handle_write_char - Print a single character with provided formatting.
 * @c: The character to be printed.
 * @buffer: The buffer array for handling printing operations.
 * @flags: Flags indicating formatting details (e.g., zero-padding, alignment).
 * @width: Minimum number of characters to output.
 * @precision: Not used in this function but present for consistency with other handlers.
 * @size: Not used in this function but present for consistency with other handlers.
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* HANDLE WRITING OF NUMBERS *************************/
/**
 * write_number - Prints a number with provided formatting.
 * @is_negative: Indicator whether the number is negative.
 * @ind: Index in the buffer where the number starts.
 * @buffer: The buffer array for handling printing operations.
 * @flags: Flags indicating formatting details.
 * @width: Minimum number of characters to output.
 * @precision: Number of digits after the decimal point.
 * @size: Not used in this function but present for consistency with other handlers.
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Helper function to handle number writing.
 * @ind: Index in the buffer where the number starts.
 * @buffer: The buffer array for handling printing operations.
 * @flags: Flags indicating formatting details.
 * @width: Minimum number of characters to output.
 * @prec: Precision, indicating how many digits to print after the decimal.
 * @length: Length of the number to print.
 * @padd: Padding character.
 * @extra_c: Extra character to prepend (e.g., '+' or '-').
 *
 * Return: Number of characters printed.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/************************* HANDLE WRITING OF UNSIGNED NUMBERS *************************/
/**
 * write_unsgnd - Prints an unsigned number with provided formatting.
 * @is_negative: Indicator if the number is negative (unused here because it's always positive).
 * @ind: Index in the buffer where the number starts.
 * @buffer: The buffer array for handling printing operations.
 * @flags: Flags indicating formatting details.
 * @width: Minimum number of characters to output.
 * @precision: Number of digits after the decimal point.
 * @size: Not used in this function but present for consistency with other handlers.
 *
 * Return: Number of characters printed.
 */
int write_unsgnd(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	/* Since it's always positive for unsigned numbers */
	UNUSED(is_negative); 

	int length = BUFF_SIZE - ind - 1;
	char padd = ' ';

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	/* Handling the special case where the number is zero and precision is zero */
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';

	/* Updating padding if precision is specified and is greater than length */
	if (precision > 0 && precision < length)
		padd = ' ';

	/* Adding zeros for precision */
	while (precision > length)
		buffer[--ind] = '0', length++;

	return (write_num(ind, buffer, flags, width, precision, length, padd, 0));
}

/******************** UTILITY FUNCTION TO SET UNUSED PARAMETERS ********************/
/**
 * UNUSED - Utility macro function to silence unused variable warnings.
 * @VAR: The variable name that is unused.
 *
 * This function is used to handle unused variables that are present for consistency.
 * For instance, size and precision might not be used in all handlers, but are present 
 * in all to maintain a consistent function signature.
 */
#define UNUSED(VAR) (void)(VAR)

/******************** MAIN FUNCTION ********************/
/* This section can have your main function or any other logic if necessary.
 * For now, I'll leave it empty.
 */

int main()
{
    /* Test cases and main logic go here. */

    return 0;
}
