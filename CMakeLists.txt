cmake_minimum_required(VERSION 4.1)
project(BFS_and_DFS_Implemention)

set(CMAKE_CXX_STANDARD 14)

add_executable(BFS_and_DFS_Implemention
        src/BFS.cpp
        src/DFS.cpp
        src/Graph.cpp
        src/Graph.h
        src/GraphVisual.cpp
        src/GraphVisual.h
        src/main.cpp
        )

target_include_directories(BFS_and_DFS_Implemention PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/bridges-cxx-windows-3.4.4/include
)

find_library(CURL_LIB
        NAMES libcurl curl
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/src/bridges-cxx-windows-3.4.4/lib
        NO_DEFAULT_PATH
)

target_link_libraries(BFS_and_DFS_Implemention PRIVATE ${CURL_LIB})
