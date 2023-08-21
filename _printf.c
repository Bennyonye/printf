#include "main.h"

/* Assuming BUFF_SIZE is meant to be defined somewhere; if not, you'd need to define it */
#define BUFF_SIZE 1024

/* Function Prototypes */
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom printf function.
 * @format: The format string.
 * Return: Number of characters printed.
 */

        int _printf(const char *format, ...)
        {
            int i, printed_chars = 0, buff_ind = 0, printed;
            int flags, width, precision, size;
            va_list list;
            char buffer[BUFF_SIZE];
            
            if (format == NULL)
                return (-1);
            
            va_start(list, format);
            
            for (i = 0; format[i] != '\0'; i++)
            {
                if (format[i] != '%')
                {
                    buffer[buff_ind++] = format[i];
                    if (buff_ind == BUFF_SIZE)
                        print_buffer(buffer, &buff_ind);
                    
                    printed_chars++;
                }
                else
                {
                    print_buffer(buffer, &buff_ind);
                    flags = get_flags(format, &i);
                    width = get_width(format, &i, list);
                    precision = get_precision(format, &i, list);
                    size = get_size(format, &i);
                    
                    /* Move past the current character. */
                    i++;
                    
                    printed = handle_print(format, &i, list, buffer, flags, width, precision, size);
                    if (printed == -1)
                        return (-1);
                    printed_chars += printed;
                }
            }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return (printed_chars);
}

/**
 * print_buffer - Print the contents of the buffer.
 * @buffer: Array of characters (the buffer).
 * @buff_ind: Current buffer index (also represents buffer length).
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
    {
        write(1, buffer, *buff_ind);
        *buff_ind = 0;
    }
}
