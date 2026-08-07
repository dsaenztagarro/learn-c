#include <stdio.h>
#include <limits.h>

#define UNSIGNED_INT_FOO 1234U
#define UNSIGNED_INT_BAR 1234u
#define UNSIGNED_LONG_FOO 1234UL
#define UNSIGNED_LONG_BAR 1234ul

int main()
{
    printf("%-15s %25d %25d\n", "char", SCHAR_MIN, SCHAR_MAX);
    printf("%-15s %25d %25d\n", "unsigned char", 0, UCHAR_MAX);
    printf("%-15s %25d %25d\n", "short", SHRT_MIN, SHRT_MAX);
    printf("%-15s %25d %25d\n", "unsigned short", 0, USHRT_MAX);
    printf("%-15s %25d %25d\n", "int", INT_MIN,  INT_MAX);
    printf("%-15s %25d %25u\n", "unsigned int", 0,  UINT_MAX);
    printf("%-15s %25ld %25ld\n", "long", LONG_MIN, LONG_MAX);
    printf("%-15s %25d %25lu\n", "unsigned long", 0,  ULONG_MAX);
    /*       ^ left aligned text */

    return 0;
}
