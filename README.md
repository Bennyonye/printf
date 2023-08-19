# 0x11. C - printf

## Requirements

### General
1. Allowed editors: vi, vim, emacs
2. All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
3. All your files should end with a new line
4. A README.md file, at the root of the folder of the project is mandatory
5. Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
6. You are not allowed to use global variables
7. No more than 5 functions per file
8. In the following examples, the main.c files are shown as examples. You can use them to test your functions, but you don’t have to push them to your repo (if you do we won’t take them into account). We will use our own main.c files at compilation. Our main.c files might be different from the one shown in the examples
9. The prototypes of all your functions should be included in your header file called main.h
10. Don’t forget to push your header file
11. All your header files should be include guarded
12. Note that we will not provide the _putchar function for this project

## More Info

### Authorized functions and macros
1. write (man 2 write)
2. malloc (man 3 malloc)
3. free (man 3 free)
4. va_start (man 3 va_start)
5. va_end (man 3 va_end)
6. va_copy (man 3 va_copy)
7. va_arg (man 3 va_arg)

### Compilation
1. Your code will be compiled this way:
   $ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c
2. As a consequence, be careful not to push any c file containing a main function in the root directory of your project (you could have a test folder containing all your tests files including main functions)
3. Our main files will include your main header file (main.h): #include main.h
4. You might want to look at the gcc flag -Wno-format when testing with your _printf and the standard printf.
5. We strongly encourage you to work all together on a set of tests
6. If the task does not specify what to do with an edge case, do the same as printf

## Copyright - Plagiarism
1. You are tasked to come up with solutions for the tasks below yourself to meet with the above learning objectives.
2. You will not be able to meet the objectives of this or any following project by copying and pasting someone else’s work.
3. You are not allowed to publish any content of this project.
4. Any form of plagiarism is strictly forbidden and will result in removal from the program.
