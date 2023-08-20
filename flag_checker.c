#include "main.h"

/**
 * flag_checker - Calculates active flags from the format string.
 * @format: Formatted string in which to check for flags.
 * @i: Pointer to the index where flag checking starts.
 * Return: Bitwise representation of the set flags.
 */
int get_flags(const char *format, int *i)
{
    /* Mapping of flags to their corresponding bitwise values. */
    const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    int j;
    int flags = 0;

    for (*i = *i + 1; format[*i] != '\0'; (*i)++)
    {
        int found = 0;
        for (j = 0; FLAGS_CH[j] != '\0'; j++)
        {
            if (format[*i] == FLAGS_CH[j])
            {
                flags |= FLAGS_ARR[j];
                found = 1;
                break;
            }
        }

        /* If no flag character is found, break from the loop. */
        if (!found)
        {
            break;
        }
    }

    /* Move the pointer back to the last checked character. */
    (*i)--;

    return flags;
}
