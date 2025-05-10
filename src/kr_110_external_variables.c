#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int max;               /* maximum length seen so far */
char line[MAXLINE];    /* current input line */
char longest[MAXLINE]; /* longest line saved here */
/* ^ external variables DEFINITION, exactly once, outside of any function
 *
 *   Common practice is to place definitions of all external variables at the
 *   beginning of the source file, and then omit all extern declarations.
 *
 *   The usual practice is to collect extern declarations of variables and
 *   functions in a separate file, historically called a header, that is included
 *   by #include at the front of each source file.
 *   The suffix .h is conventional for header names.
 */

int getline(void);
void copy(void);
/*        ^ the word void must be used for an explicitly empty list */

int main() {
    int len;
    /* ^ automatic variables (local variables) */
    extern int max;
    extern char longest[];
    /* ^ external variable DECLARATION
     *   Must happen before it can be used in the function
     *   Can be omitted if the DEFINITION of an external variable occurs in the
     *   source file before its use in a particular function.
     *   The extern declarations in main, getline and copy are thus
     *   redundant.
     */

    max = 0;
    while ((len = getline()) > 0)
        if (len > max) {
            max = len;
            copy();
        }
    if (max > 0) /* there was a line */
        printf("%s", longest);
    return 0;
}

/* getline: specialized version */
int getline(void) {
    int c, i;
    extern char line[];
    /* ^ external variable DECLARATION */

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: specialized version */
void copy(void) {
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
