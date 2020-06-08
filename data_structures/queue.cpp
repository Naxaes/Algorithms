#include "queue.h"

#include <cstdio>


int main()
{
    Queue<int> queue (5);

    queue.Enqueue(0);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);

    printf("%d ", queue.Dequeue());
    printf("%d ", queue.Dequeue());

    queue.Enqueue(4);
    queue.Enqueue(0);

    printf("%d ", queue.Dequeue());
    printf("%d ", queue.Dequeue());
    printf("%d ", queue.Dequeue());
    printf("%d ", queue.Dequeue());
}
