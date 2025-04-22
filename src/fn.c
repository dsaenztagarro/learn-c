#include <stdio.h>

int power(int m, int n);
/*                   ^ we could even omit parameter names: `int power(int, int);`
 *            ^ parameter names need not agree with definition
 * ^ function prototype (must match definition)
 */

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
{
    int i, p;

    p = 1;
    for (i = 1; i <= n; ++i)
        p = p * base;
    return p;
}
