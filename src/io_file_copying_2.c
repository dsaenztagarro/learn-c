#include <stdio.h> // EOF

/* copy input to output; 2nd version */
int main()
{
    int c;
    // ^ 2 bytes (16 bits)

    while ((c = getchar()) != EOF)
    //                     ^ precedence of != is higher that that of =, so
    //                       parentheses are needed around the assignment
    //      ^ In C, any assignment is an expression an has a value, which is the
    //        value of the left hand side after the assignment
        putchar(c);


    printf("EOF: %d", EOF);

    printf("Boolean: %d", getchar() != EOF);
}
