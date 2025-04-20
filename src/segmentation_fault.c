#include <stdio.h> // fgets printf
#include <stdlib.h> // malloc

int main(int argc, char **argv)
{
    char *buf;
//       ^ Declares a pointer to a character (used as a string buffer).

    buf = malloc(1<<31);
//               ^ 1 << 31 is a bitwise left shift: 1 x 2^31 = 2,147,483,648 (~2.1 GB)
//                 Problem: On 32-bit systems, this exceeds the maximum allocatable
//                 memory (~2 GB), causing malloc to return NULL.
//                 Even on 64-bit systems, allocating 2.1 GB may fail due to memory constraints.

//        ^ void *malloc( size_t size );
//          Allocates size bytes of uninitialized storage.

    fgets(buf, 1024, stdin);
    printf("%s\n", buf);
//                 ^ If malloc fails, buf becomes NULL, leading to undefined
//                   behavior (crash) in fgets and printf.

    return 1;
}
