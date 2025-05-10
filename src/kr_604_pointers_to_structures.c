#include <stdio.h>
#include <ctype.h> /* isalpha isspace */
#include <string.h> /* strcmp */
#include "kr_util.h"

struct {
    char c;
    int i;
} example __attribute__((unused));
/* ^ Don't assume that the size of a structure is the sum of the sizes of its
 *   members. Because of alignment requirements for different objects, there
 *   maybe unnamed "holes" in a structure. */

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

#define MAXWORD 100

struct key *binsearch(char *, struct key *, int);

/* count C keywords; pointer version */
int main()
{
    char word[MAXWORD];
    struct key *p;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
    for (p = keytab; p < keytab + NKEYS; p++)
    /* ^ if p is a pointer to a structure, arithmetic on p takes into account
     *   the size of the structure, so p++ increments p by the correct amount
     *   to get the next element of the array of structures */
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
struct key *binsearch(char * word, struct key *tab, int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    /* ^ the language definition does guarantee that pointer arithmetic that
     *   involves the first element beyond the end of an array (that is &tab[n])
     *   will work correctly
     */
    struct key *mid;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return NULL;
}
/* ^ when a function returns a complicated type like a structure pointer,
 *   the function name can be hard to see, and to find with a text editor.
 *   Accordingly an alternate style is sometimes used:
 *
 *   struct key*
 *   binsearch(char * word, struct key *tab, int n)
 */
