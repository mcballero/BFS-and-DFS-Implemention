cmake_minimum_required(VERSION 4.1)
project(BFS_and_DFS_Implemention)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BFS_and_DFS_Implemention
        src/BFS.cpp
        src/Graph.cpp
        src/Graph.h)
