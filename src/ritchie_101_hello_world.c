#include <stdio.h>
/*       ^ When the name is bracketed by < and > a search is made for the header
 *         in a standard set of places (for example, on UNIX systems, typically
 *         in the directory /usr/include
 *
 *         1. The Preprocessing and Compilation Phase
 *         The C Preprocessor replaces this line with the content of stdio.h
 *         header file. What does this do?
 *         It brings in declarations (not implementations) for standard I/O
 *         functions such as printf, as well as types and macros.
 *
 *         For example, it effectively inserts a line like:
 *         `extern int printf(const char *format, ...);`
 *
 *         This tells the compiler that somewhere there is a function called
 *         printf you can call, and how to call it
 *
 */

int main()
/* ^ default return type is `int`, so it can be omitted, but generates compiler warning */
{
    printf("hello, world\n");
    /*                   ^ escape sequence */
    /* 2. The Linking Phase
     * When you compile your program and it contains a call to `printf`,
     * the compiler knows how to check your usage (thanks to the declaration
     * from `stdio.h`), but the actual code for `printf` is not in your source
     * file.
     *
     * During the linking phase, the linker looks for the actual implementation
     * of printf.
     *
     * The implementation of printf is found in the standard C library
     * (often called libc).
     *
     * The linker automatically links your program to this library, finding the
     * compiled machine code for printf and connecting your call to it
     */
    return 0;
}
