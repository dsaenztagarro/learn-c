/* Cube a variable using call by reference */
#include <stdio.h>

int cubeByValue(int);

int main()
{
    int number = 5;

    printf("The original value of number is %d\n", number);
    number = cubeByValue(number);
    printf("The new value of number is %d\n", number);
    return 0;
}

int cubeByValue(int n)
{
    return n * n * n; /* cube local variable n */
}
