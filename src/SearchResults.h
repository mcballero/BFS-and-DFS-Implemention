// use this structure to return comparable results 
// across BFS and DFS.
#ifndef SEARCH_RESULTS_H
#define SEARCH_RESULTS_H

#include <vector>
#include <cstddef>

struct SearchResults {
    bool found = false; // was the search successful?

    std::vector<int> path; // final number of nodes path.size(), final number of edges is path.size -1

    std::vector<int> visitedOrder; 

    std::size_t nodesVisited = 0; // number of nodes checked

    std::size_t edgesExamined = 0; // number of edges checked

    double runtimeMs = 0.0;
};

#endif

