#include <stdio.h> // printf

/* print Fahrenheit-Celsisu table
    for fahr = 0, 20, ..., 300 */
// ^ multiline comment
int main()
{
    int fahr, celsius;
    int lower, upper, step;
    // ^ declaration: a type name and a list of variables

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    while (fahr <= upper) {
        celsius = 5 * (fahr-32) / 9;
        //          ^ integer division truncates (any fractional part is discarded)
        //            (5/9) will be truncated to zero
        printf("%3d\t%6d\n", fahr, celsius);
        //       ^ %d specifies an integer argument
        //         %3d prints numbers right-justified in a field at least 3 digits wide
        fahr = fahr + step;
    }
    // ^ the body of while can be a single statement without braces
}
