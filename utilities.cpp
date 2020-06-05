#include "utilities.h"

void PrintArray(int* array, size_t count)
{
    for (size_t i = 0; i < count-1; ++i)
        printf("%d ", array[i]);
    printf("%d\n", array[count-1]);
}