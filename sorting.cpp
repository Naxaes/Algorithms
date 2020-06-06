#include <iostream>

#include "utilities.h"
#include "data_structures/heap.h"


// Time Complexity: O(n*2)
// Auxiliary Space: O(1)
// Boundary Cases: Insertion sort takes maximum time to sort if elements are sorted in reverse order. And it takes minimum time (Order of n) when elements are already sorted.
// Sorting In Place: Yes
// Stable: Yes
// Online: Yes
template <class T>
void InsertionSort(T* array, size_t count)
{
    if (count <= 1)
        return;

    for (size_t i = 1; i < count; ++i)
    {
        T element = array[i];

        size_t j = i - 1;
        while (j >= 0 && element < array[j])
        {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = element;
    }
}



// Worst and Average Case Time Complexity: O(n*n). Worst case occurs when array is reverse sorted.
// Best Case Time Complexity: O(n). Best case occurs when array is already sorted.
// Boundary Cases: Bubble sort takes minimum time (Order of n) when elements are already sorted.
// Auxiliary Space: O(1)
// Sorting In Place: Yes
// Stable: Yes
template <class T>
void BubbleSort(T* array, size_t count)
{
    if (count <= 1)
        return;

    bool swapped = false;

    for (size_t i = 0; i < count - 1; ++i)
    {
        for (size_t j = 0; j < count - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                Swap(&array[j], &array[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            return;
    }
}


// Time Complexity: O(n2) as there are two nested loops.
// Auxiliary Space: O(1). The good thing about selection sort is it never makes more than O(n) swaps and can be useful when memory write is a costly operation.
// Stable: No, but can be made.
// Sorting In Place: Yes.
template <class T>
void SelectionSort(T* array, size_t count)
{
    if (count <= 1)
        return;

    for (size_t i = 0; i < count - 1; ++i)
    {
        size_t index_of_min = i;

        for (size_t j = i; j < count; ++j)
            if (array[j] < array[index_of_min])
                index_of_min = j;

        Swap(&array[i], &array[index_of_min]);
    }
}


// https://www.geeksforgeeks.org/merge-sort/
// Time Complexity: Sorting arrays on different machines. Merge Sort is a recursive algorithm and time complexity can be expressed as following recurrence relation.
// T(n) = 2T(n/2) + \Theta(n)
// The above recurrence can be solved either using Recurrence Tree method or Master method. It falls in case II of Master Method and solution of the recurrence is \Theta(nLogn).
// Time complexity of Merge Sort is \Theta(nLogn) in all 3 cases (worst, average and best) as merge sort always divides the array into two halves and take linear time to merge two halves.
// Auxiliary Space: O(n)
// Algorithmic Paradigm: Divide and Conquer
// Sorting In Place: No in a typical implementation
// Stable: Yes
template <class T>
void Merge(T* array, size_t left, size_t middle, size_t right, T* storage)
{
    size_t left_count  = middle - left;
    size_t right_count = right - middle;

    T* left_array  = storage;
    T* right_array = storage + middle;

    Copy(left_array,  left_count,  array + left,   right);
    Copy(right_array, right_count, array + middle, right);

    size_t i = left;
    size_t left_i  = 0;
    size_t right_i = 0;

    while (left_i < left_count && right_i < right_count)
    {
        if (left_array[left_i] <= right_array[right_i])
            array[i++] = left_array[left_i++];
        else
            array[i++] = right_array[right_i++];
    }

    while (left_i < left_count)
        array[i++] = left_array[left_i++];
    while (right_i < right_count)
        array[i++] = right_array[right_i++];
}
template <class T>
void MergeSortHelper(T* array, size_t left, size_t right, T* result)
{
    if (left < right - 1)
    {
        size_t middle = (left + right) / 2;    // (l+r) / 2  = l + (r-l) / 2;

        MergeSortHelper(array, left,   middle, result);
        MergeSortHelper(array, middle, right,  result);

        Merge(array, left, middle, right, result);
    }
}
template <class T>
void MergeSort(T* array, size_t count)
{
    T* result = new T[count];
    MergeSortHelper(array, 0, count, result);
    delete[] result;
}


// https://www.geeksforgeeks.org/quick-sort/
// Best Case Time Complexity: \theta(n Log n). The best case occurs when the partition process always picks the middle element as pivot. T(n) = 2T(n/2) + \theta(n).
// Average Case Time Complexity: O(n Log n). T(n) = T(n/9) + T(9n/10) + \theta(n)
// Worst Case Time Complexity: O(n2)
// Auxiliary Space: O(1)
// Sorting In Place: No, extra space is needed for the recursion.
// Stable: No
template <class T>
size_t Partition(T* array, size_t left, size_t right)
{
    T pivot = array[right-1];

    size_t i = left;
    for (size_t j = left; j < right; j++)
        if (array[j] < pivot)
            Swap(&array[i++], &array[j]);

    Swap(&array[i], &array[right-1]);
    return i;
}
template <class T>
void QuickSortHelper(T* array, size_t left, size_t right)
{
    if (left < right - 1)
    {
        size_t pivot_index = Partition(array, left, right);

        QuickSortHelper(array, left, pivot_index);
        QuickSortHelper(array, pivot_index + 1, right);
    }
}
template <class T>
void QuickSort(T* array, size_t count)
{
    QuickSortHelper(array, 0, count);
}


// Time Complexity: Time complexity of heapify is O(Log n). Time complexity of BuildMaxHeap() is O(n). The overall time complexity of Heap Sort is O(n Log n).
// Auxiliary Space: O(1)
// Sorting In Place: No, extra space is needed for the recursion.
// Stable: No
// Heap sort algorithm has limited uses because Quicksort and Mergesort are better in practice.
template <class T>
void HeapSort(T* array, size_t count)
{
    if (count <= 1)
        return;

    BuildMaxHeap(array, count);

    for (size_t i = count-1; i != static_cast<size_t>(-1); --i)  // NOTE(ted): Beware of underflow.
    {
        Swap(&array[0], &array[i]);
        Heapify(array, i, 0);
    }
}


// Time Complexity: O(n^2)
// Auxiliary Space: O(1)
// Sorting In Place: Yes
// Stable: No
//
template <class T>
void ShellSort(T* array, size_t count)
{
    // h_k = ceil(h'_k) where h'_k = 2.25 * h'_{k-1} + 1, and h'_1 = 1
    size_t gaps[] = { 701, 301, 132, 57, 1, 4, 10, 23 };

    for (size_t gap = count / 2; gap > 0; gap /= 2)
    {
        for (size_t i = gap; i < count; ++i)
        {
            T element = array[i];

            size_t j = i;
            while (j >= gap && array[j - gap] > element)
            {
                array[j] = array[j - gap];
                j -= gap;
            }

            array[j] = element;
        }
    }
}


template <class T>
void CountingSort(T* array, size_t count)
{
    const auto& [minimum, maximum] = MinMax(array, count);

    size_t k = maximum - minimum + 1;

    auto* counter = new size_t[k];
    memset(counter, 0, k * sizeof(size_t));

    auto* input = new T[k];
    memcpy(input, array, count * sizeof(T));

    for (size_t i = 0; i < count; ++i)
        counter[input[i] - minimum] += 1;

    size_t total = 0;
    for (size_t i = 0; i < k; ++i)
    {
        T temp = counter[i];
        counter[i] = total;
        total += temp;
    }

    for (size_t i = 0; i < count; ++i)
    {
        size_t x = input[i] - minimum;
        array[counter[x]] = x;
        counter[x] += 1;
    }

    delete[] counter;
    delete[] input;
}


int main()
{
    {
        printf("InsertionSort:  ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        InsertionSort(array, ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }

    {
        printf("BubbleSort:     ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        BubbleSort(array, ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }

    {
        printf("SelectionSort:  ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        SelectionSort(array, ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }

    {
        printf("MergeSort:      ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        MergeSort(array,  ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }

    {
        printf("QuickSort:      ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        QuickSort(array,  ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }

    {
        printf("HeapSort:       ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        HeapSort(array,   ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }
    {
        printf("ShellSort:      ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        ShellSort(array,  ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }
    {
        printf("CountingSort:   ");
        int array[] = {6, 3, 2, 0, 1, 5, 8, 7, 9, 4};
        CountingSort(array,  ARRAY_SIZE(array));
        PrintArray(array, ARRAY_SIZE(array));
    }
}