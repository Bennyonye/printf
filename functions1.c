#include "main.h"

/*************** DISPLAY UNSIGNED NUMBER ******************/
/**
 * display_unsigned - Showcases an unsigned integer
 * @types: Argument list
 * @buffer: Array buffer for display
 * @flags:  Current flag status
 * @width: Column width
 * @precision: Decimal precision
 * @size: Value size
 * Return: Count of chars displayed.
 */
int display_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/*************** DISPLAY UNSIGNED OCTAL VALUE *************/
/**
 * display_octal - Showcases an unsigned integer in octal
 * @types: Argument list
 * @buffer: Array buffer for display
 * @flags:  Current flag status
 * @width: Column width
 * @precision: Decimal precision
 * @size: Value size
 * Return: Count of chars displayed.
 */
int display_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************ DISPLAY UNSIGNED HEXADECIMAL VALUE ***********/
/**
 * display_hex - Showcases an unsigned integer in hex
 * @types: Argument list
 * @buffer: Array buffer for display
 * @flags:  Current flag status
 * @width: Column width
 * @precision: Decimal precision
 * @size: Value size
 * Return: Count of chars displayed.
 */
int display_hex(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (render_hex(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/******** DISPLAY UNSIGNED HEXADECIMAL IN UPPERCASE *********/
/**
 * display_hex_upper - Showcases an unsigned integer in uppercase hex
 * @types: Argument list
 * @buffer: Array buffer for display
 * @flags:  Current flag status
 * @width: Column width
 * @precision: Decimal precision
 * @size: Value size
 * Return: Count of chars displayed.
 */
int display_hex_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (render_hex(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/********** RENDER HEXADECIMAL IN VARIOUS FORMATS **********/
/**
 * render_hex - Renders hex values in various styles
 * @types: Argument list
 * @map_to: Mapping array
 * @buffer: Array buffer for display
 * @flags:  Current flag status
 * @flag_ch: Active flag character
 * @width: Column width
 * @precision: Decimal precision
 * @size: Value size
 * Return: Count of chars displayed.
 */
int render_hex(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

        return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

