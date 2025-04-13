#include <stdio.h>
#include <stdlib.h> // atoi

unsigned int factorial(unsigned int n)
{                        // ^ qualifier for `int` and `char`
    if (n == 0)
        return 1;

    return n * factorial(n -1);
}

int main(int argc, char **argv)
{
    unsigned int loop = 50;
    if (argc == 2) {
        loop = atoi(argv[1]);
        //      ^ ASCII to int
        //        Interprets an integer value in a byte string pointed to by argv[1]
    }
    while (loop--) {
        printf("Factorial of number %d is %u\n",
                loop,
                factorial(loop));
    }
    return 0;
}
