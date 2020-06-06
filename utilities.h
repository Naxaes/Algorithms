#pragma once

#include <cstddef>
#include <stdexcept>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

template <class T>
inline void Swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <class T>
inline void Copy(T* array_a, size_t count_a, T* array_b, size_t count_b)
{
    if (count_a > count_b)
        throw std::runtime_error("Destination array is smaller than source.");

    for (size_t i = 0; i < count_a; ++i)
        array_a[i] = array_b[i];
}

template <class T>
inline std::pair<T, T> MinMax(T* array, size_t count)
{
    T minimum = array[0];
    T maximum = array[0];

    for (size_t i = 0; i < count; ++i)
        if (array[i] < minimum)
            minimum = array[i];
        else if (array[i] > maximum)
            maximum = array[i];

    return { minimum, maximum };
}

template <class T>
inline T Min(T* array, size_t count)
{
    T minimum = array[0];
    for (size_t i = 0; i < count; ++i)
        if (array[i] < minimum)
            minimum = array[i];
    return minimum;
}

template <class T>
inline T Max(T* array, size_t count)
{
    T maximum = array[0];
    for (size_t i = 0; i < count; ++i)
        if (array[i] > maximum)
            maximum = array[i];
    return maximum;
}

void PrintArray(int* array, size_t count);