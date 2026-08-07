#include <stdio.h>

int main()
{
    int c, nl;

    nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
/*                ^ a character written between single quotes represents an
 *                  integer value equal to the numerical value of the character
 *                  in the machine's character set.
 *                  This is called a character constant
 */
            ++nl;
    printf("%d\n", nl);

    printf("%d", 'A');
    /*            ^ 'A' is a character constant; in the ASCII character set its
     *              value is 65
     */
    return 0;
}

/* ASCII - American Standard Code for Information Interchange
 * Standard ASCII uses 7 bits; allowing for 128 unique codes (0 - 127)
 * Extended ASCII uses 8 bits; (0 - 255)
 *
 * All modern character encodings (like UTF-8 and Unicode) include ASCII as
 * their first 128 characters for compatibility
 */
