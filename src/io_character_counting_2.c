#include <stdio.h>

/* count characters in input; 1st version */
int main()
{
    double nc;

    nc = 0;

    for (nc = 0; getchar() != EOF; ++nc)
        ;
    /*  ^ the isolated semicolon, called a null statement, is there to satisfy
     *    the body of the loop (empty)
     */

    printf("%.0f\n", nc);
    /*       ^ printf uses %f for both float and double; %0.f suppresses
     *         printing of the decimal point and the fraction part, which is
     *         zero.
     */

    return 0;
}
