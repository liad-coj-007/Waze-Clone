cmake_minimum_required(VERSION 3.22.1)
project(WAZE VERSION 1.0 LANGUAGES CXX)

add_executable(main main.cpp Graph.cpp Utilities.cpp Vertex.cpp
CompByDist.cpp Road.cpp Dist.cpp Heap.cpp)