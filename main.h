#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/* Struct definition */
typedef struct fmt
{
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
} fmt_t;

/* Main functions */
int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i, va_list list, char buffer[],
                 int flags, int width, int precision, int size);

/* Printing Functions */
int print_char(va_list, char[], int, int, int, int);
int print_string(va_list, char[], int, int, int, int);
int print_percent(va_list, char[], int, int, int, int);

/* Number handling functions */
int print_int(va_list, char[], int, int, int, int);
int print_binary(va_list, char[], int, int, int, int);
int print_unsigned(va_list, char[], int, int, int, int);
int print_octal(va_list, char[], int, int, int, int);
int print_hexadecimal(va_list, char[], int, int, int, int);
int print_hexa_upper(va_list, char[], int, int, int, int);
int print_hexa(va_list, char[], char[], int, char, int, int, int);
int print_non_printable(va_list, char[], int, int, int, int);
int print_pointer(va_list, char[], int, int, int, int);
int print_reverse(va_list, char[], int, int, int, int);
int print_rot13string(va_list, char[], int, int, int, int);

/* Specifiers Handling functions */
int flags_checker(const char *, int *);
int width_parser(const char *, int *, va_list);
int get_precision(const char *, int *, va_list);
int format_size(const char *, int *);

/* Width handler functions */
int handle_write_char(char, char[], int, int, int, int);
int write_number(int, int, char[], int, int, int, int);
int write_num(int, char[], int, int, int, int, char, char);
int write_pointer(char[], int, int, int, int, char, char, int);
int write_unsgnd(int, int, char[], int, int, int, int);

/* Utilities */
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);
long int convert_size_number(long int num, int size);
unsigned long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
