#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */

void strcpy1(char*, char*);
void strcpy2(char*, char*);
void strcpy3(char*, char*);
void strcpy4(char*, char*);

int main()
{
    char dest[10] = "foo";
    /* ^ `"foo"` is a string literal, which indeeds resides in read-only memory.
     *   `char dest[10] = "foo";` creates a new, writable array of 10 `char`
     *   elements on the stack (if local) or in writable data (if global).
     *   The compiler copies the contents of the string literal
     *   ('f', 'o', 'o', '\0') into the first four elements of `arr`.
     *   The remaining elements (`dest[4]` to `arr[9]`) are zero-initialized.
     *   After initialization, `dest` is a writable array containing a copy of
     *   the string literal, not a pointer to the literal.
     */
    char *src = "bar";
    /* ^ Here `src` points directly to the read-only string literal "bar".
     *   Modifying `*src` is undefined behavior (often a crash)
     */

    strcpy1(dest, src);
    printf("dest: %s\tsrc: %s\n", dest, src);

    char *dest1 = malloc(4 * sizeof(char));
    /*           ^ extern void *malloc (size_t __size) */

    strcpy1(dest1, src);
    printf("dest1: %s\tsrc: %s\n", dest1, src);

    char *dest2 = malloc(4 * sizeof *dest2);
    /* ^ sizeof can be used with either a type (in parentheses, e.g., `sizeof(int)`)
     *   or an expression (without parentheses, e.g., `sizeof x`).
     *   `sizeof *dest2` returns the size of the type that `dest2` points to,
     *   without actually dereferencing the pointer (no memory access occurs)
     */

    strcpy3(dest2, src);
    printf("dest2: %s\tsrc: %s\n", dest2, src);

    char *dest3 = malloc(4 * sizeof *dest3);
    char src2[10] = "bar";

    strcpy4(dest3, src2);
    printf("dest3: %s\tsrc2: %s\n", dest3, src2);

    char dest4[10] = "foo";

    strcpy(dest4, src2);
    printf("dest4: %s\tsrc2: %s\n", dest4, src2);

    free(dest1);
    free(dest2);
    free(dest3);
    /* ^ The free function is only for memory you allocate dynamically
     *   (e.g., with malloc, calloc, or realloc).
     *
     *   The memory block that malloc allocates is always contiguous in
     *   virtual memory-that is, the pointer returned by malloc(size) points
     *   to a block of memory of exactly size bytes, and all those bytes are
     *   sequential in the program’s address space. You can safely use array
     *   indexing and pointer arithmetic within that block, just as you would
     *   with a statically allocated array.
     *
     *   Contiguous in virtual memory does not mean contiguous in physical RAM.
     *   The operating system may map the virtual memory pages to any physical
     *   locations, and user programs (including C code using malloc) cannot
     *   see or control this
     *
     *   Different malloc calls do not guarantee contiguous blocks. Each call
     *   may return a pointer to a completely different region of memory
     */
    return 0;
}

/* strcpy: copy t to s; array subscript version */
void strcpy1(char *s, char *t)
{
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

/* strcpy: copy t to s; pointer version 1 */
void strcpy2(char *s, char *t)
{
    while ((*s++ = *t++) != '\0') {
        s++;
        t++;
    }
}

/* strcpy: copy t to s; pointer version 2 */
void strcpy3(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
}

/* strcpy: copy t to s; pointer version 3 */
void strcpy4(char *s, char *t)
{
    while ((*s++ = *t++)) /* use parentheses around assigment used as truth value */
        ;
}
