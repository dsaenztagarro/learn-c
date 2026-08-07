#include <stdio.h>
#include <string.h>
#include <ctype.h> /* isalpha */
#include "kr_util.h" /* getch ungetch */

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;              /* type of the last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

/* undcl: convert word description to declaration
 *
 * The program is a recursive-descent parser.
 *
 * Example: "x is a function returning a pointer to an array of pointers
 * to functions returning char".
 * Input: "x () * [] * () char *"
 * Output: "char (*(*x())[])()"
 */
int main()
{
    int type;
    char temp[MAXTOKEN];

    while(gettoken() != EOF) {
        strcpy(out, token);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wformat-overflow="
        while((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                sprintf(temp, "(*%s)", out); /* warning overflow */
                strcpy(out, temp);
            } else if (type == NAME) { /* e.g. token = "int" */
                sprintf(temp, "%s %s", token, out); /* warning overflow */
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        printf("%s\n", out);
        #pragma GCC diagnostic pop
    }
    return 0;
}

int gettoken(void)  /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
             *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}
