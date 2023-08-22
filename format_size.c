#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: Pointer to the current index in format string.
 *
 * Return: Size type (e.g., S_LONG, S_SHORT, or 0 for default).
 */
int format_size(const char *format, int *i)
{
    /* The character after the current one */
    int next_char = *i + 1;
    int size = 0;

    if (format[next_char] == 'l')
    {
        size = S_LONG;
    }
    else if (format[next_char] == 'h')
    {
        size = S_SHORT;
    }

    /* Update the index pointer only if a size modifier is found */
    if (size != 0)
    {
        *i = next_char;
    }

    return size;
}
