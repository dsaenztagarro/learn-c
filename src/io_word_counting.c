#include <stdio.h>

// Read chars:
// - from file:     ./bin/io_word_counting <infile
// - from keyboard: ./bin/io_word_counting

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
int main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
//  ^ sets all three variables to zero. This is not a special case, but a
//    consequence of the fact that an assigment is an expression with a value
//    and assignments associate from right to left. It's as if we had written
//
//    nl = (nw = (nc = 0))

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}

