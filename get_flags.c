#include "main.h"

/* ============================ FUNCTION ============================ */
/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: Index to keep track of the position in the format string.
 * Return: Flags: Integer representing the combination of flags.
 */
int get_flags(const char *format, int *i)
{
    /* ----------- VARIABLES DECLARATION ----------- */
    /* Flags characters and corresponding bitwise representations */
    const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};
    int j, curr_i; 
    int flags = 0;

    /* ----------- CALCULATE FLAGS ----------- */
    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        for (j = 0; FLAGS_CH[j] != '\0'; j++)
            if (format[curr_i] == FLAGS_CH[j])
            {
                flags |= FLAGS_ARR[j];
                break;
            }

        if (FLAGS_CH[j] == 0)
            break;
    }

    *i = curr_i - 1;

    return (flags);
}
