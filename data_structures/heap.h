#pragma once

#include <memory>

#include "../utilities.h"

using std::unique_ptr;
using std::make_unique;


size_t GetLeftChild(size_t parent_index);
size_t GetRightChild(size_t parent_index);
size_t GetParent(size_t child_index);


template <typename T>
void Heapify(T* array, size_t count, size_t index)
{
    size_t largest_index     = index;
    size_t left_child_index  = GetLeftChild(index);
    size_t right_child_index = GetRightChild(index);

    if (left_child_index < count && array[left_child_index] > array[largest_index])
        largest_index = left_child_index;

    if (right_child_index < count && array[right_child_index] > array[largest_index])
        largest_index = right_child_index;

    if (largest_index != index)
    {
        Swap(&array[index], &array[largest_index]);
        Heapify(array, count, largest_index);
    }
}

template <typename T>
void BuildMaxHeap(T* array, size_t count)
{
    // We only need to heapify from the last (bottom-right-most) parent, as heapify will
    // swap with the children to pertain the heap property.
    size_t last_parent = GetParent(count-1);
    for (size_t i = last_parent + 1; i--; )  // NOTE(ted): Beware of underflow.
        Heapify(array, count, i);
}


// https://en.wikipedia.org/wiki/Binary_heap#Building_a_heap
template <typename T>
class MaxHeap
{
public:
    explicit MaxHeap(size_t max_count) : data(make_unique<T[]>(max_count)), count(0), max_count(max_count) {}
    explicit MaxHeap(const T* array, size_t count) : data(make_unique<T[]>(count)), count(count), max_count(count)
    {
        for (size_t i = 0; i < count; ++i)
            this->Add(array[i]);
    }

    template <class ... Targs>
    void Add(Targs&& ... args)
    {
        ++this->count;
        if (this->count >= this->max_count)
            throw std::runtime_error("Buffer overflown");

        size_t child_index      = this->count - 1;
        this->data[child_index] = T(std::forward<Targs>(args)...);

        size_t parent_index = GetParent(child_index);

        while (this->data[parent_index] < this->data[child_index])
        {
            Swap(&this->data[child_index], &this->data[parent_index]);

            child_index  = parent_index;
            parent_index = GetParent(child_index);
        }
    }

    T Pop(size_t index)
    {
        if (this->count == 0)
            throw std::runtime_error("Index out of bounds.");

        --this->count;

        T result = this->data[index];
        Swap(&this->data[index], &this->data[this->count]);

        size_t parent_index = index;

        while (true)
        {
            size_t left_child_index  = GetLeftChild(parent_index);
            size_t right_child_index = GetRightChild(parent_index);

            if (left_child_index < this->count && this->data[left_child_index] > this->data[parent_index])
            {
                Swap(&this->data[left_child_index], &this->data[parent_index]);
                parent_index = left_child_index;
            }
            else if (right_child_index < this->count && this->data[right_child_index] > this->data[parent_index])
            {
                Swap(&this->data[right_child_index], &this->data[parent_index]);
                parent_index = right_child_index;
            }
            else
            {
                break;
            }
        }

        return result;
    }

    [[nodiscard]] const T* RawArray() const { return data.get(); }
    [[nodiscard]] size_t   Count()    const { return count; }

private:
    unique_ptr<T[]> data;
    size_t count;
    size_t max_count;
};
