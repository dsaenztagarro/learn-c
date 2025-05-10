#include <stdio.h>
#include <ctype.h> /* isalpha */
#include <string.h> /* strcmp */
#include "kr_util.h"

#define NKEYS (sizeof keytab / sizeof keytab[0])
/* the size of the array is the size of one entry times the number of entries
 *
 * Using `sizeof(keytab[0])` over `sizeof(struct key)` has the advantage that
 * it does not need to be changed if the type changes.
 */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    /* ... */
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};
#pragma GCC diagnostic pop
/* ^ The initializers are listed in pairs corresponding to the structure members.
 * It would be more precise to enclose initializers for each "row" or structure
 * in braces, as in
 *
 *   { "auto", 0 },
 *   { "break", 0 },
 *   { "case", 0 },
 *   ...
 *
 * but the inner braces are not necessary when the initializers are simple
 * variables or character strings, and whn all are present.
 *
 * As usual, the number of entries in the array keytab will be computed if
 * initializers are present and the [] is left empty.
 */

#define MAXWORD 100

int binsearch(char *, struct key *, int);

/* count C keywords */
/* STDIN: const const continue auto const void void */
int main()
{
    printf("NKEYS: %ld\n", NKEYS);

    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        /* ^ each call to getword finds a word, which is copied into the array
         *   named as its first argument. */
        if (isalpha(word[0]))
            /* ^ int isalpha( int ch );
             *   Checks if the given character is an alphabetic character */
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char * word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
