#include <stdio.h> /* getchar */
#include <string.h> /* strcpy */
#include <stdlib.h> /* atof */
#include "ritchie_util.h"

/***************************
 * 5.4 Address Arithmethic
 ***************************/

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */
/* ^ This could have also been written:
 *
 *   static char *allocp = &allocbuf[0];
 */

char *alloc(int n) /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
        /* ^ a pointer and an integer may be added or substracted.
         *   The construction `ptr + n` means the address of the n-th object
         *   beyond the one ptr currently points to.
         *   This is true regardless of the kind of object ptr points to;
         *   n is scaled according to the size of the objects ptr points to,
         *   which is determined by the declaration of ptr.
         *   If an int is four bytes, for example, the int will be scaled by
         *   four.
         *
         *   Pointer substraction is also valid: if p and q point to elements
         *   of the same array, and p<q, then q-p+1 is the number of elements
         *   from p to q inclusive.
         */
    } else /* not enough room */
        return 0;
        /*     ^ The symbolic constant NULL is often used in place of zero,
         *       as a mnemonic to indicate more clearly that this is a special
         *       value for a pointer. NULL is defined in <stdio.h>
         */
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/***********************************************
 * 5.6 Pointers to Arrays; Pointers to Pointers
 ***********************************************/

#define MAXLEN 1000

static int getline(char s[], int lim);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            /* ^ char *strcpy( char *dest, const char *src );  (until C99)
             *   Copies the null-terminated byte string pointed to by src,
             *   including the null terminator, to the character array
             *   whose first element is pointed by dest.
             */
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines; lineptr treated as an array */
/*
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}
*/

/* writelines: write output lines; lineptr treated as a pointer */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
    /*                  ^
     *  Initially *lineptr points to the first line; each increment advances it
     *  to the next line pointer while nlines is counted down.
     */
}

/* Why Use static?
 * 1. Prevents name collisions:
 *    Two different .c files can each have a `static void helper_function(void)`,
 *    and they will not conflict during linking, because each is only visible
 *    within its own file.
 * 2. Encapsulation:
 *    Keeps implementation details private to the file, similar to "private"
 *    methods in other languages.
 */
static int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/***************************
 * 5.4 Address Arithmethic
 ***************************/

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}
