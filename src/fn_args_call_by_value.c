#include <stdio.h>

int power(int m, int n);

/* test power function */
int main()
{
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2,i), power(-3,i));

    return 0;
    /*     ^ a return value of zero signals normal termination */
}

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
/*                      ^ function args are passed "by value"
 *                        called function is given the values of its arguments
 *                        in temporary variables rather than the originals.
 */
{
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}
