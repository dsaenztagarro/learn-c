/* Concept: system */
/* Source: linux:030300 */
#include <stdio.h>
#include <gnu/libc-version.h>

int main()
{
    const char *libc_version;

    libc_version = gnu_get_libc_version();

    printf("__GLIBC__: %d\n", __GLIBC__);
    printf("__GLIBC_MINOR__: %d\n", __GLIBC_MINOR__);
    printf("libc_version: %s\n", libc_version);
    return 0;
}
