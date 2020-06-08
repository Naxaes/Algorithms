#pragma once


#pragma once

#include <memory>

#include "../debug.h"

using std::unique_ptr;
using std::make_unique;

template <class T>
class Stack
{
public:
    constexpr static size_t INITIAL_CAPACITY = 8;

    Stack()                            : data(make_unique<T[]>(INITIAL_CAPACITY)), count(0),     capacity(INITIAL_CAPACITY) {}
    explicit Stack(size_t capacity)    : data(make_unique<T[]>(capacity)),         count(0),     capacity(capacity) {}
    Stack(const T* data, size_t count) : data(make_unique<T[]>(count)),            count(count), capacity(count)
    {
        for (size_t i = 0; i < count; ++i)
            this->data[i] = data[i];
    }
    Stack(const std::initializer_list<T> data) : data(make_unique<T[]>(data.size())), count(data.size()), capacity(data.size())
    {
        size_t i = 0;
        for (auto it = data.begin(); it != data.end(); ++it)
            this->data[i] = *it;
    }

    bool IsFull()  const noexcept { return this->count == this->capacity; }
    bool IsEmpty() const noexcept { return this->count == 0;              }

    template <class ... Targs>
    void Push(Targs&& ... args)
    {
        DEBUG_BLOCK(if (IsFull()) throw std::runtime_error("Index out of bounds."); );

        this->data[this->count++] = T(std::forward<Targs>(args)...);
    }

    T& Pop()
    {
        DEBUG_BLOCK(if (IsEmpty()) throw std::runtime_error("Queue is already empty."); );

        T& result = this->data[this->count--];
        return result;
    }

    size_t Count() const noexcept { return this->count; }


private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t count;
};