#include <stdio.h>

void displayBits(unsigned);

int main()
{
    unsigned number1, number2, mask, setBits;

    number1 = 65535;
    mask = 1;
    printf("The result of combining the following\n");
    displayBits(number1);
    displayBits(mask);
    printf("using the bitwise AND operator & is\n");
    displayBits(number1 & mask);

    number1 = 15;
    setBits = 241;
    printf("The result of combining the following\n");
    displayBits(number1);
    displayBits(setBits);
    printf("using the bitwise inclusive OR operator | is\n");
    displayBits(number1 | setBits);

    number1 = 139;
    number2 = 199;
    printf("The result of combining the following\n");
    displayBits(number1);
    displayBits(number2);
    printf("using the bitwise exclusive OR operator ^ is\n");
    displayBits(number1 ^ number2);

    number1 = 21845;
    printf("The one's complement of\n");
    displayBits(number1);
    printf("is\n");
    displayBits(~number1);

    return 0;
}

void displayBits(unsigned value)
{
    unsigned c, displayMask = 1 << 15;

    printf("%7u = ", value);

    for (c = 1; c <= 16; c++) {
        putchar(value & displayMask ? '1' : '0');
        value <<= 1;

        if (c % 8 == 0)
            putchar(' ');
        /* ^ print in groups of 8 bits */
    }

    putchar('\n');
}

/* Bit 1    Bit 2   Bit 1 & Bit 2
*  0        0       0
*  1        0       0
*  0        1       0
*  1        1       1 */

/* Bit 1    Bit 2   Bit 1 | Bit 2
*  0        0       0
*  1        0       1
*  0        1       1
*  1        1       1 */

/* Bit 1    Bit 2   Bit 1 ^ Bit 2
*  0        0       0
*  1        0       1
*  0        1       1
*  1        1       0 */
