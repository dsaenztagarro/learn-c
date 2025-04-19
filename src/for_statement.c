#include <stdio.h> // printf

/* print Fahrenheit-Celsisu table */
int main()
{
    int fahr;

    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    //  ^ the body of the loop can be a single statement, or a group of
    //    statements enclosed in braces

    printf("\n");

    for (fahr = 300; fahr >= 0; fahr = fahr - 20)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
