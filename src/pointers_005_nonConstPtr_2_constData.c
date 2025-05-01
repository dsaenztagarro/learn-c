/* Printing a string one character at a time */
/* a non-constant pointer to constant data   */
#include <stdio.h>

void printCharacters(const char *);

int main()
{
    char string[] = "print characters of a string";

    printf("The string is:\n");
    printCharacters(string);
    putchar('\n');
    return 0;
}

void printCharacters(const char *s)
{
    for( ; *s != '\0'; s++)  /* no initialization */
        putchar(*s);
}
