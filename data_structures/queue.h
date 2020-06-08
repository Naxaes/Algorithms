#pragma once

#include <memory>

#include "../debug.h"

using std::unique_ptr;
using std::make_unique;

template <class T>
class Queue
{
public:
    constexpr static size_t INITIAL_CAPACITY = 8;

    Queue()                            : data(make_unique<T[]>(INITIAL_CAPACITY)), count(0),     front(0), back(0),       capacity(INITIAL_CAPACITY) {}
    explicit Queue(size_t capacity)    : data(make_unique<T[]>(capacity)),         count(0),     front(0), back(0),       capacity(capacity) {}
    Queue(const T* data, size_t count) : data(make_unique<T[]>(count)),            count(count), front(0), back(count-1), capacity(count)
    {
        for (size_t i = 0; i < count; ++i)
            this->data[i] = data[i];
    }
    Queue(const std::initializer_list<T> data) : data(make_unique<T[]>(data.size())), count(data.size()), front(0), back(data.size()-1), capacity(data.size())
    {
        size_t i = 0;
        for (auto it = data.begin(); it != data.end(); ++it)
            this->data[i] = *it;
    }

    bool IsFull()  const noexcept { return this->count == this->capacity; }
    bool IsEmpty() const noexcept { return this->count == 0;              }

    template <class ... Targs>
    void Enqueue(Targs&& ... args)
    {
        DEBUG_BLOCK(if (IsFull()) throw std::runtime_error("Index out of bounds."); );

        this->data[this->back] = T(std::forward<Targs>(args)...);
        this->back = (this->back + 1) % this->capacity;
        ++this->count;
    }

    T& Dequeue()
    {
        DEBUG_BLOCK(if (IsEmpty()) throw std::runtime_error("Queue is already empty."); );

        T& result = this->data[this->front];
        this->front = (this->front + 1) % this->capacity;
        --this->count;

        return result;
    }

    size_t Count() const noexcept { return this->count; }


private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t count;
    size_t front;
    size_t back;
};