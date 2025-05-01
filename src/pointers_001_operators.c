#include <stdio.h>

int main()
{
    int a;      /* a is an integer */
    int *aPtr;  /* aPtr is a pointer to an integer */

    a = 7;
    aPtr = &a;  /* aPtr set to address of a */
    /* the unary operator & gives the address of an object */

    printf("The address of a is %p\n", &a);
    printf("The address of aPtr is %p\n", &aPtr);
    printf("The value of aPtr is %p\n\n", aPtr);
    /* %p extracts address memory as hexadecimal */

    printf("The value of a is %d\n", a);
    printf("The value of *aPtr is %d\n\n", *aPtr);
    /* the unary operator * is the indirection or dereferencing operator */

    printf("Proving that * and & are complements of each other.\n");
    printf("&*aPtr = %p\n*&aPtr = %p\n", &*aPtr, *&aPtr);

    return 0;
}
