#include "union_find.h"

#include <memory>
#include <iostream>


using std::unique_ptr;
using std::make_unique;


class QuickFind
{
public:
    const size_t capacity;

    explicit QuickFind(size_t capacity) : capacity(capacity), id(make_unique<size_t[]>(capacity))
    {
        for (size_t i = 0; i < capacity; ++i)
            this->id[i] = i;
    }

    [[nodiscard]]
    inline bool Connected(size_t a, size_t b) const noexcept { return this->id[a] == this->id[b]; }

    void Union(size_t a, size_t b) const noexcept
    {
        size_t id_a = this->id[a];
        size_t id_b = this->id[b];

        for (size_t i = 0; i < capacity; ++i)
            if (this->id[i] == id_b)
                this->id[i] = id_a;
    }

private:
    unique_ptr<size_t[]> id;
};


class QuickUnion
{
public:
    const size_t capacity;

    explicit QuickUnion(size_t capacity) : capacity(capacity), id(make_unique<size_t[]>(capacity))
    {
        for (size_t i = 0; i < capacity; ++i)
            this->id[i] = i;
    }

    [[nodiscard]]
    inline bool Connected(size_t a, size_t b) const noexcept
    {
        size_t root_a = FindRoot(a);
        size_t root_b = FindRoot(b);

        return root_a == root_b;
    }

    void Union(size_t a, size_t b) const noexcept
    {
        size_t root_a = FindRoot(a);
        this->id[b] = root_a;
    }

private:
    [[nodiscard]]
    size_t FindRoot(size_t node) const
    {
        size_t parent = this->id[node];
        while (parent != node)
        {
            node = parent;
            parent = this->id[parent];
        }
        return node;
    }


    unique_ptr<size_t[]> id;
};


class WeightedUnion
{
public:
    const size_t capacity;

    explicit WeightedUnion(size_t capacity) : capacity(capacity), id(make_unique<size_t[]>(capacity)), tree_size(make_unique<size_t[]>(capacity))
    {
        for (size_t i = 0; i < capacity; ++i)
        {
            this->id[i] = i;
            this->tree_size[i] = 1;
        }
    }

    [[nodiscard]]
    inline bool Connected(size_t a, size_t b) const noexcept
    {
        size_t root_a = FindRoot(a);
        size_t root_b = FindRoot(b);

        return root_a == root_b;
    }

    void Union(size_t a, size_t b) const noexcept
    {
        size_t root_a = FindRoot(a);
        size_t root_b = FindRoot(b);

        if (root_a == root_b)
            return;

        if (this->tree_size[root_a] > this->tree_size[root_b])
        {
            this->id[b] = root_a;
            this->tree_size[root_a] += this->tree_size[root_b];
        }
        else
        {
            this->id[a] = root_b;
            this->tree_size[root_b] += this->tree_size[root_a];
        }
    }

private:
    [[nodiscard]]
    size_t FindRoot(size_t node) const
    {
        size_t parent = this->id[node];
        while (parent != node)
        {
            node = parent;
            parent = this->id[parent];
        }
        return node;
    }


    unique_ptr<size_t[]> id;
    unique_ptr<size_t[]> tree_size;
};


class WQUPC  // Weighted Quick Union with Path Compression
{
public:
    const size_t capacity;

    explicit WQUPC(size_t capacity) : capacity(capacity), id(make_unique<size_t[]>(capacity)), tree_size(make_unique<size_t[]>(capacity))
    {
        for (size_t i = 0; i < capacity; ++i)
        {
            this->id[i] = i;
            this->tree_size[i] = 1;
        }
    }

    [[nodiscard]]
    inline bool Connected(size_t a, size_t b) const noexcept
    {
        size_t root_a = FindRoot(a);
        size_t root_b = FindRoot(b);

        return root_a == root_b;
    }

    void Union(size_t a, size_t b) const noexcept
    {
        size_t root_a = FindRoot(a);
        size_t root_b = FindRoot(b);

        if (root_a == root_b)
            return;

        if (this->tree_size[root_a] > this->tree_size[root_b])
        {
            this->id[b] = root_a;
            this->tree_size[root_a] += this->tree_size[root_b];
        }
        else
        {
            this->id[a] = root_b;
            this->tree_size[root_b] += this->tree_size[root_a];
        }
    }

private:
    [[nodiscard]]
    size_t FindRoot(size_t node) const
    {
        while (node != this->id[node])
        {
            this->id[node] = this->id[this->id[node]];  // Path compression.
            node = this->id[node];
        }
        return node;
    }


    unique_ptr<size_t[]> id;
    unique_ptr<size_t[]> tree_size;
};


template <class Union>
void TestUnion()
{
    Union union_find(10);

    union_find.Union(0, 1);
    union_find.Union(1, 2);
    union_find.Union(2, 3);
    union_find.Union(3, 4);
    union_find.Union(4, 5);

    union_find.Union(6, 7);
    union_find.Union(7, 8);
    union_find.Union(8, 9);

    std::cout << "---- START ----\n";

    std::cout << "Connected 1: " << union_find.Connected(0, 3) << '\n';
    std::cout << "Connected 1: " << union_find.Connected(0, 5) << '\n';
    std::cout << "Connected 1: " << union_find.Connected(2, 3) << '\n';

    std::cout << "Connected 2: " << union_find.Connected(6, 7) << '\n';
    std::cout << "Connected 2: " << union_find.Connected(6, 9) << '\n';

    std::cout << "Dis-Connected: " << union_find.Connected(0, 9) << '\n';
    std::cout << "Dis-Connected: " << union_find.Connected(3, 7) << '\n';
    std::cout << "Dis-Connected: " << union_find.Connected(5, 6) << '\n';

    std::cout << "---- STOP ----\n\n" << std::endl;
}



int main()
{
    TestUnion<QuickFind>();
    TestUnion<QuickUnion>();
    TestUnion<WeightedUnion>();
    TestUnion<WQUPC>();
}
