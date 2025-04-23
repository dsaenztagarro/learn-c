enum boolean { NO, YES };
/* ^ an enumeration is a list of constant integer values
 *   The first name in an enum has value 0, the next 1, and so on, unless explicit
 *   values are specified.
 */

enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
/*                  ^ If not all values specified, unspecified values continue
 *                    the progression from the last specified value
 */

enum same_values { FOO = 1, BAR = 1 };
/*                       ^ Values need not be distinct in the same enumeration */

/* Names in different enumerations must be different */

int main()
{
    return 0;
}
