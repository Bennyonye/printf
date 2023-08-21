#include "main.h"

/*=================== Character Handling Functions ===================*/

/**
 * handle_write_char - Render a single character.
 * @c: Target character to write.
 * @buffer: Temporary buffer for handling the character.
 * @flags: Active format flags.
 * @width: Width specifier.
 * @precision: Precision of the character rendering.
 * @size: Size control specifier.
 *
 * Return: Count of rendered characters.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padding_char = ' ';
	char extra_char = 0;  /* Added declaration */

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding_char = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding_char;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/*=================== Numeric Handling Functions ===================*/

int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int num_length = BUFF_SIZE - ind - 1;
	char padding_char = ' ';
	char extra_char = 0;  /* Added declaration */

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding_char = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (render_num(ind, buffer, flags, width, precision,
		num_length, padding_char, extra_char));
}

int render_num(int ind, char buffer[], int flags, int width, 
               int precision, int num_length, char padding_char, 
               char extra_char)
{
	int i;  /* Added declaration */

	if (extra_char != 0)
		num_length++;
	if (width > num_length)
	{
		for (i = 1; i < width - num_length + 1; i++)
			buffer[i] = padding_char;
		buffer[i] = '\0';
		if (flags & F_MINUS)
			return (write(1, &buffer[ind], num_length) + write(1, &buffer[1], i - 1));
		else
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], num_length));
	}
	return (write(1, &buffer[ind], num_length));
}

int render_unsigned(int is_negative, int ind,
	char buffer[], int flags, int width, int precision)
{
	int num_length = BUFF_SIZE - ind - 1;
	char padding_char = ' ';

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < num_length)
		padding_char = ' ';

	while (precision > num_length)
	{
		buffer[--ind] = '0';
		num_length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding_char = '0';
	return (write_buffer(ind, buffer, flags, width, num_length, padding_char));
}

int write_buffer(int ind, char buffer[], int flags, 
                 int width, int num_length, char padding_char)
{
	int i;  /* Added declaration */

	if (width > num_length)
	{
		for (i = 1; i < width - num_length + 1; i++)
			buffer[i] = padding_char;
		buffer[i] = '\0';
		if (flags & F_MINUS)
			return (write(1, &buffer[ind], num_length) + write(1, &buffer[1], i - 1));
		else
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], num_length));
	}
	return (write(1, &buffer[ind], num_length));
}

