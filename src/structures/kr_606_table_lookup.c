#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h> /* strdup */
#include "kr_util.h" /* strdup */

#define HASHSIZE 101

struct nlist {      /* table entry: */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name */
    char *defn;             /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
/* produces a starting index in the array hashtab */
unsigned hash(char *s)
{
    unsigned hashval;
    /* ^ Unsigned arithmetic ensures that the hash value is non-negative
     *   WHY?
     *   1. Well-defined Wrapping Behavior
     *   In C, unsigned integer arithmetic is defined to wrap around modulo 2^n
     *   (where n is the number of bits in the type).
     *   That is, if an unsigned value exceeds its maximum, it wraps back to
     *   zero in a well-defined manner.
     *   Using unsigned guarantees that the hash computation will always
     *   produce a valid, predictable value, even if the calculation overflows.
     *
     *   2. Hash Functions Expect Overflow
     *   Hash functions are designed so that overflow is expected and even
     *   desired: it helps "mix" the bits and spread the values evenly.
     *
     *   3. Consistency with Other Hash Functions
     *   Most hash functions in C use unsigned types for their internal state
     *   and return value for this exact reason.
     *
     *   4. Portability and Size
     *   unsigned is guaranteed to be able to hold at least the range 0 to 65535,
     *   and on most modern systems is 32 bits wide, which is plenty for hash
     *   table indices.
     */

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    /* WHY?
     *
     * 1. Prime number properties
     * 31 is a prime number, which helps distribute hash values more uniformly
     * across the table. Primes reduce collisions because they share no common factors with most numbers
     *
     * 2. Polynomial Rolling Hash
     * The hash function computes a polynomial of the form:
     *
     * hashval = s0 * 31^n-1 + s1 * 31^n-2 + ... + sn-1
     *
     * Each character’s ASCII value is weighted by a power of 31, ensuring that
     * even small differences in the string propagate to distinct hash values.
     *
     * 3. Bitwise efficiency
     * 31 = 32 - 1, which allows compilers to optimize `31 * x` as `(x << 5) - x`
     * (shift left by 5 bits = multiply by 32, then substract x).
     *
     * This was useful historically for performance but is less critical today.
     */
    return hashval % HASHSIZE;
    /*             ^ The modulus ensure final index fits inside the hash table */
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        /* ^ standard idiom to walk a linked list
         *   for (ptr = head; ptr != NULL; ptr = ptr->next)
         */
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;        /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    /* ^ same that "unsigned int" */

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else      /* already there */
        free((void *) np->defn);    /* free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}


int main()
{
    int i;
    struct nlist *ptr;

    struct {
        char *name;
        char *defn;
    } examples[] = {
        { "NUM", "10" },
        { "MAX", "100" },
        { "MIN" , "0" }
    };

    for (i = 0; i < 3; i++)
        install(examples[i].name, examples[i].defn);


    char *names[] = { "MIN", "NUM", "MAX" };

    for (i = 0; i < 3; i++) {
        ptr = lookup(names[i]);
        printf("%s: %s\n", names[i], ptr->defn);
    }

    return 0;
}
