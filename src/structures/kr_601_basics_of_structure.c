#include <stdio.h>
#include <math.h>
/* ^ this gives you the declaration of sqrt, so the compiler knows how to check
 *   your code.
 *   The actual implementation of sqrt is in the math library (libm),
 *   which is not linked automatically.
 *   The linker needs to be told explicitly to include this library.
 *   gcc yourfile.c -o yourprog -lm
 */

struct point {
    int x;
    int y;
};
/* An optional name called structure tag may follow the word struct
 * (as with point here) */

struct rect {
    struct point pt1;
    struct point pt2;
};
/* Structures can be nested */

int main()
{
    struct point pt __attribute__((unused));
    /*              ^ this syntax is a GCC (and Clang) compiler extension that
     *                you attach to a variable, function, or parameter to
     *                explicitly tell the compiler:
     *                “I know this might be unused, and that’s intentional-don’t
     *                warn me about it
     *
     * Defines a variable pt which is a structure of type "struct point"
     */

    struct point pt1 = { 320, 200 };
    /* A structure can be initialized by following its definition with a list
     * of initializers, each a constant expression, for the members */

    printf("%d,%d\n", pt1.x, pt1.y);

    double dist, sqrt(double);

    dist = sqrt((double)pt1.x * pt1.x + (double)pt1.y * pt1.y);

    printf("dist: %f\n", dist);

    return 0;
}
