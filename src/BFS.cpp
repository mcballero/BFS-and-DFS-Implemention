//
// Created by Maria Caballero on 10/29/26.
//

#include "Graph.h"
#include <vector>
#include <string>

using namespace std;

struct SearchResult { //result format for metrics
    bool found;
    vector<int> path;
    vector<int> visitedOrder;
    size_t nodesVisited;
    size_t edgesExamined;
    double runtimeMs;
};

