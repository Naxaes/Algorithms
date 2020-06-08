#pragma once

#include <iostream>
#include <stdexcept>
#include <cstddef>

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
inline void Reverse(T* array, size_t count)
{
    for (size_t i = 0; i < count / 2; ++i)
        Swap(&array[i], &array[count - i - 1]);
}

template <class T>
inline std::pair<T, T> MinMax(const T* array, size_t count)
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
inline T Min(const T* array, size_t count)
{
    T minimum = array[0];
    for (size_t i = 0; i < count; ++i)
        if (array[i] < minimum)
            minimum = array[i];
    return minimum;
}

template <class T>
inline T Max(const T* array, size_t count)
{
    T maximum = array[0];
    for (size_t i = 0; i < count; ++i)
        if (array[i] > maximum)
            maximum = array[i];
    return maximum;
}
template <class T>
inline bool InRange(T value, T minimum, T maximum)
{
    return (minimum <= value && value < maximum);
}
template <class T>
inline void BoundsCheck(T value, T minimum, T maximum)
{
    if (!InRange(value, minimum, maximum))
        throw std::runtime_error("Index out of bounds");
}

template <class T>
void PrintArray(const T* array, size_t count)
{
    if (count == 0)
    {
        std::cout << "(empty)" << std::endl;
        return;
    }

    for (size_t i = 0; i < count - 1; ++i)
        std::cout << array[i] << " ";
    std::cout << array[count - 1] << std::endl;
}