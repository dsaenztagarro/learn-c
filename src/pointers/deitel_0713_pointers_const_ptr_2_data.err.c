/* Attempting to modify a constant pointer to non-constant data */
#include <stdio.h>

int main()
{
    int x, y;
    int * const ptr = &x;

    *ptr = 5; /* ptr updates value stored in the address it points to */
              /* address stored by ptr keeps constant */

    ptr = &y; /* ERROR: attempt to modify address stored by ptr */
    return = 0;
}
