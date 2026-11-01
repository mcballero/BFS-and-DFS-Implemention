#ifndef BFS_H
#define BFS_H

#include "SearchResults.h"
#include "Graph.h"

class BFS{   
public:
    static SearchResults search(const Graph& graph, int start, int target); // call w/o bfs obj
};

#endif