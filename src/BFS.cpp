#include "SearchResults.h"
#include "BFS.h"
#include "Graph.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <chrono>

using namespace std;

SearchResults BFS::search(const Graph& graph, int start, int target) {
    auto startTime = chrono::high_resolution_clock::now(); // start timer

    SearchResults result; // create a SearchResults object to store the results of the search

    // if either node doesn't exist, return result with found = false
    if (!graph.hasNode(start) || !graph.hasNode(target)) { 
        auto endTime = chrono::high_resolution_clock::now(); //end timer 

        result.runtimeMs =
            chrono::duration<double, std::milli>(endTime - startTime).count();
        return result;
    }

    queue<int> q; // queue for BFS
    unordered_set<int> visited; // set to keep track of visited nodes
    unordered_map<int, int> parent; // map to keep track of the parent of each node 

    q.push(start); 
    visited.insert(start);

    while (!q.empty()) {

        int current = q.front();
        q.pop();

        result.visitedOrder.push_back(current);

        // did we already reach taregt?
        if (current == target) {
            result.found = true;
            break;
        }

        const std::vector<int>& neighbors = graph.getNeighbors(current);

        for (int neighbor : neighbors) { // go though connected nodes
            result.edgesExamined++; // increment edges examined

            if (visited.find(neighbor) == visited.end()) { // if neighbor hasn't been visited
                visited.insert(neighbor);
                parent[neighbor] = current; 
                q.push(neighbor); // add neighbor to queue
            }
        }

    }

    result.nodesVisited = result.visitedOrder.size();

    if (result.found) { //path reconstruction 

        int current = target;

        while (current != start) {
            result.path.push_back(current);
            current = parent[current];
        }

        // Add the starting node.
        result.path.push_back(start);

        // Reverse so the path goes from start to target.
        std::reverse(result.path.begin(), result.path.end());
    }


    auto endTime = chrono::high_resolution_clock::now();
    result.runtimeMs = chrono::duration<double, std::milli>(endTime - startTime).count();
    
    return result;
}