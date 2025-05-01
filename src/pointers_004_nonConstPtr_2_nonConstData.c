/* Converting lowercase letters to uppercase letters */
/* using a non-constant pointer to non-constant data */
#include <stdio.h>

void convertToUppercase(char *);

int main()
{
    char string[] = "characters";

    printf("The string before conversion is: %s\n", string);
    convertToUppercase(string);
    printf("The string after conversion is: %s\n", string);
    return 0;
}

void convertToUppercase(char *s)
{
    while (*s != '\0') {
        if (*s >= 'a' && *s <= 'z')
            *s -= 32; /* convert to ASCII uppercase letter */

        ++s; /* increment s to point to the next character */
             /* in other words, increment by one the address stored in the pointer */
    }
}
