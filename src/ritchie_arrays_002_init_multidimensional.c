/* Initializing multidimensional arrays */
#include <stdio.h>

void printArray(int [][3]);

int main()
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmissing-braces"
    int array1[2][3] = { {1, 2, 3}, {4, 5, 6} },
        array2[2][3] = { 1, 2, 3, 4, 5 },       /* warning: missing braces around initializer */
        array3[2][3] = { {1, 2}, 4 },           /* warning: missing braces around initializer */
        array4[3][3] = { {1}, {2}, {3}, {4} },  /* warning: excess elements in array initializer */
        array5[4][3] = { {1}, {2, 3}, {4, 5, 6}, {7} };
    #pragma GCC diagnostic pop
    /* ^
     * a #pragma is a compiler directive that provides additional
     * information or instructions to the compiler, beyond what the
     * standard language syntax can express
     * Pragmas are not standardized across all compilers.
     * Each compiler may support different pragmas, and unrecognized
     * pragmas are typically ignored
     */

    printf("Values in array1 row are:\n");
    printArray(array1);

    printf("Values in array2 row are:\n");
    printArray(array2);

    printf("Values in array3 row are:\n");
    printArray(array3);

    printf("Values in array4 row are:\n");
    printArray(array4);

    printf("Values in array5 row are:\n");
    printArray(array5);

    return 0;
}

void printArray(int a[][3])
{
    int i, j;

    for (i = 0; i <= 1; i++) {

        for (j = 0; j <= 2; j++)
            printf("%d ", a[i][j]);

        printf("\n");
    }
}
