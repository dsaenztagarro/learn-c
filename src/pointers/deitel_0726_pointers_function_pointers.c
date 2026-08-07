/* Multipurpose sorting program using function pointers */
#include <stdio.h>
#define SIZE 10

void bubble(int *, const int, int (*)(int, int));
int ascending(const int, const int);
int descending(const int, const int);

int main()
{
    int a[SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};
    int counter, order;

    printf("Enter 1 to sort in ascending order,\n");
    printf("Enter 2 to sort in descending order:");
    scanf("%d", &order);

    printf("\nData items in original order\n");

    for (counter = 0; counter <= SIZE - 1; counter++)
        printf("%4d", a[counter]);

    if (order == 1) {
        bubble(a, SIZE, ascending);
        printf("\nData items in ascending order\n");
    }
    else {
        bubble(a, SIZE, descending);
        printf("\nData items in descending order\n");
    }

    for (counter = 0; counter <= SIZE - 1; counter++)
        printf("%4d", a[counter]);

    printf("\n");

    return 0;
}

void bubble(int *work, const int size, int (*compare)(int, int))
{                                       /*   ^ compare is a pointer to a function */
    int pass, count;
    void swap(int *, int *);

    for (pass = 1; pass <= size - 1; pass++)

        for (count = 0; count <= size - 2; count++)
            if ((*compare)(work[count], work[count + 1]))
                swap(&work[count], &work[count + 1]);

    /*      if (compare(work[count], work[count + 1]))
     *
     *      Equivalent, but it is not explicit you are using a pointer to function
     */
}

void swap(int *element1Ptr, int *element2Ptr)
{
    int temp;

    temp = *element1Ptr;
    *element1Ptr = *element2Ptr;
    *element2Ptr = temp;
}

int ascending(const int a, const int b)
{
    return b < a;
}

int descending(const int a, const int b)
{
    return b > a;
}
