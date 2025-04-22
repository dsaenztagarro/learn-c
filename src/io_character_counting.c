#include <stdio.h>

/* count characters in input; 1st version */
int main()
{
    long nc;
/*  ^ 4 bytes (32 bits) */

    nc = 0;
    while (getchar() != EOF)
/*         ^ "functions" like getchar and putchar in <stdio.h> are often macros,
 *           thus avoiding the overhead of a function call per character
 */
        ++nc;
/*      ^ the increment operator, used as prefix operator, increments nc before
 *        its value is used
 */

    printf("%ld\n", nc);
/*          ^ the conversion specification %ld tells printf that the
 *            corresponding argument is a long integer
 */

    return 0;
}
