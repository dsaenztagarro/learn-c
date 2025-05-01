/* Attempting to modify a constant pointer to constant data */
#include <stdio.h>

int main()
{
    int x = 5, y;
    const int *const ptr = &x;

    *ptr = 7; /* error: assignment of read-only location `*(const int *)ptr` */
    ptr = &y; /* error: assignment of read-only variable `ptr` */
    return 0;
}
