cmake_minimum_required(VERSION 3.15)
project(Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sorting sorting.cpp utilities.cpp data_structures/heap.cpp data_structures/dynamic_array.cpp)
add_executable(Graph graphs.cpp utilities.cpp data_structures/dynamic_array.cpp)

add_executable(Heap  data_structures/heap.cpp)
add_executable(Queue data_structures/queue.cpp)
add_executable(UnionFind data_structures/union_find.cpp)


add_compile_definitions(DEBUG=1)