/*#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "SearchResults.h"
#include "GraphVisual.h"
#include "BFS.h"
#include "DFS.h"


//Right now main just makes a temp graph to test
int main() {
    Graph graph;
    //make vertices


    for (int i = 1; i < 10000; i++) {
        graph.addNode(i);
    }
    //form edges
    std::random_device seed;
    std::mt19937 rng(seed());
    std::uniform_int_distribution<int> gen(1, 10000); // uniform, unbiased
    for (int i = 1; i < 10000; i++) {
        //cout << "From: " << i << endl;
        int from = gen(rng);
        int to = gen(rng);
        //int to = i+1;
        while (to == from) {
            to = gen(rng);
        }
        //cout << "To: " << to << endl;
        graph.addEdge(from, to);
    }

    int from = gen(rng);
    int to = gen(rng);
    while (from == to) {//reroll if same
        to = gen(rng);
    }


    /*
    //CSV file graph
    ifstream file("E:/CLion/Projects/BFS-and-DFS-Implemention-main/TestGraph.csv");
    std::string row;

    //loop
    while (getline(file, row)) {
        stringstream ss(row);
        std::string vertex;

        //continue if cell empty
        if (!getline(ss, vertex, ',')) {
            continue;
        }

        //put vertex in adj list
        int vertexVal = stoi(vertex);
        graph.addNode(vertexVal);

        while (getline(ss, vertex, ',')) {
            if (vertex.empty()) {
                continue;
            }
            int neighbor = stoi(vertex);
            graph.addEdge(vertexVal, neighbor);
        }
    }
    int from = 4;
    int to = 15;
    */
/*
    SearchResults searchResultsBFS = BFS::search(graph, from, to);
    std::unordered_map<int, std::vector<int>> adjList = graph.getAdjacencyList();
    SearchResults searchResultsDFS = DFS::search(graph, from, to);
    visualizeGraph(adjList, searchResultsBFS, searchResultsDFS);

    return 0;
}*/