#pragma once

#include <memory>

using std::unique_ptr;
using std::make_unique;


template <class T>
class DynamicArray
{
public:
    constexpr static size_t INITIAL_CAPACITY = 8;

    DynamicArray() : data(make_unique<T[]>(INITIAL_CAPACITY)), count(0), capacity(INITIAL_CAPACITY) {}
    explicit DynamicArray(size_t capacity) : data(make_unique<T[]>(capacity)), count(0),    capacity(capacity) {}
    DynamicArray(T* data, size_t count)    : data(make_unique<T[]>(count)),    count(count), capacity(count)
    {
        for (size_t i = 0; i < count; ++i)
            this->data.get()[i] = data[i];
    }

    void Add(T* values, size_t count)
    {
        if (this->count + count > this->capacity)
            this->Reallocate();

        for (size_t i = 0; i < count; ++i)
            this->data.get()[this->count++] = values[i];
    }

    void Reallocate()
    {
        this->capacity *= 2;

        auto new_storage = make_unique<T[]>(this->capacity);
        memcpy(new_storage.get(), this->data.get(), this->count * sizeof(T));

        delete this->data.release();
        this->data = std::move(new_storage);
    }

    inline T* Raw() { return this->data.get(); }
    [[nodiscard]] inline size_t Count() const noexcept { return this->count; }

    T& operator[] (size_t index) const
    {
        if (0 <= index && index < this->count)
            return this->data[index];
        else
            throw std::runtime_error("Index out of bounds.");
    }

private:
    unique_ptr<T[]> data;
    size_t count;
    size_t capacity;
};
