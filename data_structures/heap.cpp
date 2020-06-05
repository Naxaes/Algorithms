#include <memory>

#include "../utilities.h"
#include "heap.h"


size_t GetLeftChild(size_t parent_index)
{
    return 2 * parent_index + 1;
}
size_t GetRightChild(size_t parent_index)
{
    return 2 * parent_index + 2;
}
size_t GetParent(size_t child_index)
{
    if (child_index == 0)
        return 0;
    else
        return (child_index - 1) / 2;
}


//int main()
//{
//    MaxHeap<int> heap(20);
//
//    heap.Add(1);
//    heap.Add(2);
//    heap.Add(3);
//    heap.Add(7);
//    heap.Add(17);
//    heap.Add(19);
//    heap.Add(25);
//    heap.Add(36);
//    heap.Add(100);
//
//    PrintArray((int*)heap.RawArray(), heap.Count());
//
//    heap.Pop(0);
//    PrintArray((int*)heap.RawArray(), heap.Count());
//}
