#include <stdio.h> // printf

/* print Fahrenheit-Celsisu table
    for fahr = 0, 20, ..., 300 */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32);
        //                         ^ if an arithmetic operator has one floating-point
        //                           operand and one integer operand, the integer will
        //                           be converted to floating point before the operation
        //                           is done
        //         ^ a decimal point in a constant indicates that it is a floating point

        printf("%3.0f\t%6.1f\n", fahr, celsius);
        //              ^ print as floating point, at least 6 wide and 2 characters
        //                after decimal point
        fahr = fahr + step;
    }

    printf("%6.2f\n", celsius);
    //      ^ print as floating point, 2 characters after decimal point

    // octal numbers (base 8) - digits 0 to 7
    int num = 298;
    printf("number (octal): %o\n", num); // Output: (452)8 = (4*8^2 + 5*8^1 + 7*8^0 = 298)
    printf("number (hexadecimal): %x\n", num); // Output: (452)8 = (4*8^2 + 5*8^1 + 7*8^0 = 298)
    printf("number (decimal): %d\n", num);
}
