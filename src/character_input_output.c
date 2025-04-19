#include <stdio.h> // EOF

/* copy input to output; 1st version */
int main()
{
    int c;
    // ^ we can't use char since c must be big enough to hold EOF in addition
    //   to any possible char (0-255)

    c = getchar();
    while (c != EOF) {
        //      ^ Ctrl+D at an empty prompt sends the ASCII "End of Transmission"
        //        character (U+0004) to the terminal
        putchar(c);
        c = getchar();
    }

    printf("%d\n", EOF);            // Output: -1
    printf("%d", EOF == -1);        // Output: 1 (True)
    printf("%d", EOF == getchar()); // Output: 1 (True)
    //                   ^ it does not read from stdin, once the while statement
    //                     has reached EOF
    //
    // The C standard I/O library maintains internal state flags for streams
    // (like stdin), including:
    // * End-of-file (EOF) indicator: Set when an attempt is made to read past
    //   the end of input.
    // * Error indicator: Set if a read/write error occurs (e.g., disk failure).
    //   Once the EOF indicator is set for stdin, all subsequent read operations
    //   (like getchar()) will immediately return EOF without attempting to read
    //   more data.
}
