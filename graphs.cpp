#include "data_structures/dynamic_array.h"
#include "utilities.h"


template <class V, class E>
class Graph
{
public:
    Graph(V* vertices, size_t vertex_count, E* edges, size_t edge_count) :
        vertices(vertices), vertex_count(vertex_count), edges(edges), edge_count(edge_count)
    {
    }


    [[nodiscard]] V& Vertex(size_t i)  { return this->vertices[i]; }
    [[nodiscard]] E& Edge(size_t i)    { return this->edges[i];    }

    [[nodiscard]] const V& Vertex(size_t i) const { return this->vertices[i]; }
    [[nodiscard]] const E& Edge(size_t i)   const { return this->edges[i];    }

    size_t VertexCount() { return this->vertex_count; }
    size_t EdgeCount()   { return this->edge_count;   }

private:
    V* vertices;
    size_t vertex_count;

    E* edges;
    size_t edge_count;
};




template <class V, class E, class T>
void DepthFirstSearchHelper(const Graph<V, E>& graph, V vertex, V target, T& visited, DynamicArray<V>& path)
{
    if (visited[vertex])
        return;
    else
        visited[vertex] = true;

    path.Add(&vertex, 1);

    auto& neighbours = graph.Edge(vertex);
    for (size_t j = 0; j < neighbours.Count(); ++j)
    {
        DepthFirstSearchHelper(graph, neighbours[j], target, visited, path);
    }
}

template <class V, class E>
DynamicArray<V> DepthFirstSearch(Graph<V, E> graph, V target)
{
    auto visited = make_unique<bool[]>(graph.VertexCount());
    auto path    = DynamicArray<V>();

    DepthFirstSearchHelper(graph, graph.Vertex(0), target, visited, path);

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


    Graph<Node, Edge> graph(vertices, ARRAY_SIZE(vertices), edges, ARRAY_SIZE(edges));
    DynamicArray<Node> path = DepthFirstSearch(graph, Node(9));

    for (size_t i = 0; i < path.Count() - 1; ++i)
        printf("%zi ", path[i]);
    printf("%zi ", path[path.Count() - 1]);
}