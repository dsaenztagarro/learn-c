#include <stdio.h>

void qsort(int [], int, int);
void swap(int v[], int, int);

int main()
{
    int i, arr[] = { 4, 3, 2, 1 };
    qsort(arr, 0, 3);

    for (i = 0; i < 4; i++)
        printf("%d ", arr[i]);
    return 0;
}

void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    /* ^ all elements to the right of v[left] that are minor than v[left]
     *   are piled up just to the right of v[left].
     *
     *   [ v[left], <elements "<" v[left]>, <elements ">" v[left]> ]
     *                                  ^
     *                                 last
     *
     *   "last" points to the position of the last element that was piled up.
     *   Until the first element is piled up, initially "last" matches the
     *   position of v[left] (i.e. last = left).
     */
    swap(v, left, last);
    /*   [ <elements "<" v[left]>, v[left], <elements ">" v[left]> ]
     *                                 ^
     *                                last
     *
     *   "last" points now to v[left] after the switch
     */
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
