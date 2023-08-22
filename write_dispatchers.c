#include "main.h"

/******************* CHARACTER HANDLING *******************/
/**
 * handle_write_char - Display a character.
 * @c: The character to display.
 * @buffer: Data storage for handling output.
 * @flags: Determines the active flags.
 * @width: Defines the width of the output.
 * @precision: Precision specifier.
 * @size: Size specification.
 *
 * Return: Count of characters displayed.
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

/******************* NUMBER DISPLAY *******************/
/**
 * write_number - Display a sequence.
 * @is_negative: Indicator for negative values.
 * @ind: Character index.
 * @buffer: Data storage for handling output.
 * @flags: Determines the active flags.
 * @width: Defines the width of the output.
 * @precision: Precision specification.
 * @size: Size specification.
 *
 * Return: Count of characters displayed.
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
 * write_num - Outputs a number using storage.
 * @ind: Start index for the number in storage.
 * @buffer: Data storage.
 * @flags: Output specifications.
 * @width: Width definition.
 * @prec: Precision definition.
 * @length: Length of the number.
 * @padd: Padding character.
 * @extra_c: Additional character.
 *
 * Return: Count of characters outputted.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
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
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
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

/**
 * write_unsgnd - Outputs an unsigned value.
 * @is_negative: Indicator for negative values.
 * @ind: Start index for the number in storage.
 * @buffer: Data storage for handling output.
 * @flags: Output specifications.
 * @width: Width definition.
 * @precision: Precision specification.
 * @size: Size specification.
 *
 * Return: Count of characters displayed.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
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
 * write_pointer - Outputs a memory address.
 * @buffer: Storage array for characters.
 * @ind: Start index for the address in storage.
 * @length: Length of the address.
 * @width: Width definition.
 * @flags: Output specifications.
 * @padd: Padding character.
 * @extra_c: Additional character.
 * @padd_start: Starting index for padding.
 *
 * Return: Count of characters outputted.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
    int i;

    UNUSED(extra_c);

	if (width > length + 2)
	{
		for (i = 1; i < width - length; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			return (write(1, "0x", 2) +
				write(1, &buffer[ind], length) +
				write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			return (write(1, &buffer[1], i - 1) +
				write(1, "0x", 2) +
				write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			return (write(1, "0x", 2) +
				write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	return (write(1, "0x", 2) + write(1, &buffer[ind], length));
}
