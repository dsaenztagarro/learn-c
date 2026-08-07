#include <stdio.h>

#define LOWER 0     /* lower limit of table */
#define UPPER 300   /* upper limit */
#define STEP 20     /* step size */
/* ^ defines a symbolic name or symbolic constant to be a particular string of
 *   characters. Thereafter, any occurrence of name (not in quotes and not part
 *   of another name) will be replaced by the corresponding replacement text.
 *
 *   No semicolon at the end of #define line
 */

/* print Fahrenheit-Celsisu table */
int main()
{
    int fahr;

    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    return 0;
}
