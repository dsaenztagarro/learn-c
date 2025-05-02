/* sizeof operator when used on an array name */
/* returns the number of bytes in the array   */
#include <stdio.h>

int main()
{
    float array[20];
    /* ^ float variables are stored usually on 4 bytes of memory */

    printf("The number of bytes in the array is %zu\n",
           sizeof(array));
    /*     ^ The sizeof operator in C is not defined in any header file
     *       It is a built-in operator that is part of the C language
     *       itself and is recognized directly by the compiler.
     *       size_t is the correct and portable type for storing and
     *       working with the result of sizeof
     */

    /* Prints: 80 */

    printf("The number of elements in the array is %zu\n",
           sizeof(array) / sizeof(float));
    /*                                              ^
     * "z" was chosen because it is not used by any other standard length
     * modifier and is easy to remember for "size_t".
     */

    /* Prints: 20 */

    return 0;
}
