/* Concept: structures */
/* Source: deitel:ch10_05 */
/* An example of a union */
#include <stdio.h>

union number {
    int x;
    float y;
};
/* ^ A union is a variable that may hold (at different times) objects of
 *   different types and sizes, with the compiler keeping track of size and
 *   alignment requirements.
 *   Unions provide a way to manipulate different kinds of data in a single
 *   area of storage, without embedding any machine-dependent information in
 *   the program.
 *   They are analogous to variant records in Pascal.
 */

int main()
{
    union number value;

    value.x = 100;
    printf("%s\n%s\n%s%d\n%s%f\n\n",
           "Put a value in the integer member",
           "and print both members.",
           "int:   ", value.x,
           "float: ", value.y);

    value.y = 100.0;
    printf("%s\n%s\n%s%d\n%s%f\n\n",
           "Put a value in the floating member",
           "and print both members.",
           "int:   ", value.x,
           "float: ", value.y);
    return 0;
}

