cmake_minimum_required(VERSION 3.15)
project(Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sorting sorting.cpp utilities.cpp data_structures/heap.cpp)
add_executable(Heap data_structures/heap.cpp)
