#include <stdio.h>
/*       ^ When the name is bracketed by < and > a search is made for the header
 *         in a standard set of places (for example, on UNIX systems, typically
 *         in the directory /usr/include
 */

int main()
/* ^ default return type is `int`, so it can be omitted, but generates compiler warning */
{
    printf("hello, world\n");
    /*                   ^ escape sequence */
    return 0;
}
