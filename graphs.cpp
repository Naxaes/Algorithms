#include "utilities.h"
#include "data_structures/dynamic_array.h"
#include "data_structures/queue.h"
#include "data_structures/stack.h"


template <class V, class E>
class Graph
{
public:
    Graph(V* vertices, size_t vertex_count, E* edges, size_t edge_count) :
        vertices(vertices), vertex_count(vertex_count), edges(edges), edge_count(edge_count)
    {
    }


    V& Vertex(size_t i)  { return this->vertices[i]; }
    E& Edge(size_t i)    { return this->edges[i];    }

    const V& Vertex(size_t i) const { BoundsCheck(i, size_t(0), this->vertex_count); return this->vertices[i]; }
    const E& Edge(size_t i)   const { BoundsCheck(i, size_t(0), this->edge_count);   return this->edges[i];    }

    size_t VertexCount() const noexcept { return this->vertex_count; }
    size_t EdgeCount()   const noexcept { return this->edge_count;   }

private:
    V* vertices;
    size_t vertex_count;

    E* edges;
    size_t edge_count;
};



template <class T>
struct Node
{
    Node<T>* parent;
    T        value;

    Node() = default;
    Node(Node<T>* parent, T value) : parent(parent), value(value) {}
    Node<T>& operator= (const Node<T>& other)
    {
        if (&other != this)
        {
            this->parent = other.parent;
            this->value  = other.value;
        }

        return *this;
    }
};


template <class V, class E, class T>
void DepthFirstSearchHelper(const Graph<V, E>& graph, V vertex, V target, T& visited, DynamicArray<V>& path, bool& found)
{
    if (visited[vertex])
        return;
    else
        visited[vertex] = true;

    if (vertex == target)
    {
        found = true;
        return;
    }

    auto& neighbours = graph.Edge(vertex);
    for (size_t j = 0; j < neighbours.Count(); ++j)
    {
        DepthFirstSearchHelper(graph, neighbours[j], target, visited, path, found);
        if (found)
        {
            path.Add(&neighbours[j], 1);
            return;
        }
    }
}
template <class V, class E>
DynamicArray<V> DepthFirstSearch(const Graph<V, E>& graph, V start, V target)
{
    auto path    = DynamicArray<V>();
    auto visited = make_unique<bool[]>(graph.VertexCount());

    bool found = false;
    DepthFirstSearchHelper(graph, start, target, visited, path, found);

    if (found)
    {
        path.Add(&start, 1);
        Reverse(path.Raw(), path.Count());
    }

    return path;
}

template <template<class> class DataStructure, class V, class E>
DynamicArray<V> BreadthFirstSearch(const Graph<V, E>& graph, V start, V target)
{
    auto path    = DynamicArray<V>();
    auto visited = make_unique<bool[]>(graph.VertexCount());
    auto queue   = DataStructure<Node<V>>(graph.VertexCount());

    queue.Enqueue(nullptr, start);
    visited[start] = true;

    while (!queue.IsEmpty())
    {
        auto& vertex = queue.Dequeue();

        if (vertex.value == target)
        {
            path.Add(&vertex.value, 1);
            while (vertex.parent != nullptr)
            {
                vertex = *vertex.parent;
                path.Add(&vertex.value, 1);
            }

            // Reverse so we get start to target, instead of target to start.
            Reverse(path.Raw(), path.Count());

            break;
        }

        auto& neighbours = graph.Edge(vertex.value);
        for (size_t j = 0; j < neighbours.Count(); ++j)
            if (!visited[neighbours[j]])
            {
                visited[neighbours[j]] = true;
                queue.Enqueue(&vertex, neighbours[j]);
            }
    }

    return path;
}


int main()
{
    using Node = size_t;
    using Edge = DynamicArray<Node>;  // Adjacency list

    Node vertices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // Undirected edges.
    Edge edges[] = {
            /* 0 */ {1, 7, 4},
            /* 1 */ {0},
            /* 2 */ {4, 8, 5},
            /* 3 */ {5},
            /* 4 */ {0, 2, 7, 8},
            /* 5 */ {2, 8, 3, 6, 9},
            /* 6 */ {6},
            /* 7 */ {0, 4},
            /* 8 */ {4, 2, 5},
            /* 9 */ {5},
    };


    const Graph<Node, Edge> graph(vertices, ARRAY_SIZE(vertices), edges, ARRAY_SIZE(edges));

    {
        DynamicArray<Node> path = DepthFirstSearch(graph, Node(0), Node(9));
        PrintArray(path.Raw(), path.Count());
    }

    {
        DynamicArray<Node> path = BreadthFirstSearch<Queue>(graph, Node(0), Node(9));
        PrintArray(path.Raw(), path.Count());
    }
}