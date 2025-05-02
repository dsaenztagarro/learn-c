#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */

int strcmp1(char*, char*);
int strcmp2(char*, char*);

int main()
{
    char str1[10] = "foorebar";
    char str2[10] = "foobar";

    if (strcmp1(str1, str2) > 0)
        printf("%s > %s\n", str1, str2);
    else
        printf("%s <= %s\n", str1, str2);

    if (strcmp2(str1, "foozbar") > 0)
    /*                 ^ when used as a function argument, an array (including
     *                   a string literal) decays to a pointer to its first
     *                   element - so "foo" becomes of type `char *` (or, in
     *                   modern C, `const char *`).
     */
        printf("%s > foozbar\n", str1);
    else
        printf("%s <= foozbar\n", str1);

    return 0;
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp1(char *s, char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

/* pointer version */
int strcmp2(char *s, char *t)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}
