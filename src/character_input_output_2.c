#include <stdio.h> // EOF

int main()
{
    int c;
    // ^ we can't use char since c must be big enough to hold EOF in addition
    //   to any possible char

    /* 1st version */

    c = getchar();
    while (c != EOF) {
        //      ^ Ctrl+D at an empty prompt sends the ASCII "End of Transmission"
        //        character (U+0004) to the terminal
        putchar(c);
        c = getchar();
    }

    /* 2nd version */

    while ((c = getchar()) != EOF)
    //                     ^ precedence of != is higher that that of =, so
    //                       parentheses are needed around the assignment
    //      ^ In C, any assignment is an expression an has a value, which is the
    //        value of the left hand side after the assignment
        putchar(c);


    printf("EOF: %d", EOF);

    printf("Boolean: %d", getchar() != EOF);
}
