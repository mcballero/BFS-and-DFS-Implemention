#include "Graph.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Implementations

// adds


bool Graph::addNode(int nodeID) {
    return adjacencyList.emplace(nodeID, vector<int>{}).second;
}


bool Graph::addEdge(int start, int end) {
    if (start == end) { // no edge connected to itself
        return false;
    }

    if (!hasNode(start) || !hasNode(end)) { // no edge connected to a node that doesn't exist
        return false;
    }

    if (hasEdge(start, end)) { // add no edge that already exists
        return false;
    }

    adjacencyList[start].push_back(end);
    adjacencyList[end].push_back(start);
    return true;
}


// removes


bool Graph::removeNode(int nodeID) {
    auto it = adjacencyList.find(nodeID);
    if (it == adjacencyList.end()) {return false;} // gets it and return false if not found

    for (auto& entry : adjacencyList) {
        auto& neighbors = entry.second; //gets each node's neighbor vector

        // remove places all nodeID instances at the end of the vector
        // erase deletes all instances
        neighbors.erase(
            std::remove(neighbors.begin(), neighbors.end(), nodeID),
            neighbors.end()
        );
    }

    adjacencyList.erase(it); // erases node
    return true;
}


bool Graph::removeEdge(int start, int end) {
    if (!hasEdge(start, end)) {return false;}

    auto removeNeighbor = [](std::vector<int>& neighbors, int nodeID) {
        neighbors.erase(
            std::remove(neighbors.begin(), neighbors.end(), nodeID),
            neighbors.end()
        );
    };

    removeNeighbor(adjacencyList[start], end);
    removeNeighbor(adjacencyList[end], start);
    return true;
}


// has - does the node/edge exist?


bool Graph::hasEdge(int start, int end) const {
    if (!hasNode(start) || !hasNode(end)) {
        return false;
    }

    auto hasNeighbor = [](const std::vector<int>& neighbors, int nodeID) {
        return std::find(neighbors.begin(), neighbors.end(), nodeID)
               != neighbors.end();
    };

    return hasNeighbor(adjacencyList.at(start), end) &&
           hasNeighbor(adjacencyList.at(end), start);
}


bool Graph::hasNode(int nodeID) const {
    return adjacencyList.find(nodeID) != adjacencyList.end();
}

// graph checks

// vector that returns all nodes a node is linked with!
const std::vector<int>& Graph::getNeighbors(int nodeID) const {
    return adjacencyList.at(nodeID); // use at to handle run_time errors if nodeID doesn't exist
}


int Graph::getNodeCount() const {
    return adjacencyList.size();
}


long long Graph::getEdgeCount() const {
    long long count = 0; // since edge value can be equal to nodes(nodes-1)/2 and we have 100k nodes that is 5 billion - use long long

    for (auto& entry : adjacencyList) { // adds up the size of each node's vector.
        auto& neighbors = entry.second;
        count += neighbors.size();
    }
    return count / 2; // goes over the connections twice so divide result
}
