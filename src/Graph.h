// Created by Maria Caballero on 10/29/26.

#ifndef BFS_AND_DFS_IMPLEMENTION_GRAPH_H
#define BFS_AND_DFS_IMPLEMENTION_GRAPH_H
#include <vector>
#include <string>
#include <unordered_map>

class Graph{
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    //adds and removes nodes
    bool addNode(int nodeID);
    bool removeNode(int nodeID);

    //adds and removes edges
    bool addEdge(int start, int end);
    bool removeEdge(int start, int end);

    //checks if nodes/edges were alr placed
    bool hasNode(int nodeID) const;
    bool hasEdge(int start, int end) const;

    //reads graph information
    const std::vector<int>& getNeighbors(int nodeID) const; // const ref doesn't modify graph
    int getNodeCount() const;
    long long getEdgeCount() const;
};


#endif //BFS_AND_DFS_IMPLEMENTION_GRAPH_H