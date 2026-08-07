/* Demonstrating an array of pointers to functions */
#include <stdio.h>

void function1(int);
void function2(int);
void function3(int);

int main()
{
    void (*f[3])(int) = {function1, function2, function3};
    int choice;

    printf("Enter a number between 0 and 2, 3 to end: ");
    scanf("%d", &choice);

    while (choice >= 0 && choice < 3) {
        (*f[choice])(choice);
        printf("Enter a number between 0 and 2, 3 to end: ");
        scanf("%d", &choice);
    }

    printf("You entered 3 to end\n");
    return 0;
}

void function1(int a)
{
    printf("You entered %d so function1 was called\n\n", a);
}

void function2(int a)
{
    printf("You entered %d so function2 was called\n\n", a);
}

void function3(int a)
{
    printf("You entered %d so function3 was called\n\n", a);
}
