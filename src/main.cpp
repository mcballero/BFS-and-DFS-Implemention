#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "SearchResults.h"
#include "GraphVisual.h"

#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int getInteger(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            return value;
        }

        cout << "Please enter a valid whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void printMenu(const Graph& graph, bool hasStart, int start, bool hasTarget, int target) {

    cout << "\n========================================\n";
    cout << "       GRAPH TRAVERSAL VISUALIZER\n";
    cout << "========================================\n";

    cout << "Graph: " << graph.getNodeCount() << " nodes | " << graph.getEdgeCount() << " edges\n";

    cout << "Start: ";
    if (hasStart) cout << start;
    else cout << "Not set";

    cout << " | Target: ";
    if (hasTarget) cout << target;
    else cout << "Not set";

    cout << "\n----------------------------------------\n";
    cout << "1. Display Graph Summary\n";
    cout << "2. Load from CSV\n";
    cout << "3. Add Node\n";
    cout << "4. Remove Node\n";
    cout << "5. Add Edge\n";
    cout << "6. Remove Edge\n";
    cout << "7. Set Start Node\n";
    cout << "8. Set Target Node\n";
    cout << "----------------------------------------\n";
    cout << "9. Run BFS\n";
    cout << "10. Run DFS\n";
    cout << "11. Compare BFS vs DFS\n";
    cout << "----------------------------------------\n";
    cout << "0. Exit\n";
}

void printResults(const string& name, const SearchResults& result) {

    cout << "\n========== " << name << " RESULTS ==========\n";

    cout << "Target found: " << (result.found ? "Yes" : "No") << '\n';

    cout << "Visited order: ";

    if (result.visitedOrder.empty()) cout << "None";

    for (int node : result.visitedOrder) {
        cout << node << ' ';
    }

    cout << "\nPath: ";

    if (!result.found) {
        cout << "No path found";
    } else {
        for (size_t i = 0; i < result.path.size(); i++) {
            cout << result.path[i];

            if (i + 1 < result.path.size()) {
                cout << " -> ";
            }
        }
    }

    cout << "\nNodes visited: " << result.nodesVisited << '\n';
    cout << "Edges examined: " << result.edgesExamined << '\n';

    cout << "Path length: ";

    if (result.found && !result.path.empty()) {
        cout << result.path.size() - 1;
    } else {
        cout << "N/A";
    }

    cout << "\nRuntime: " << result.runtimeMs << " ms\n";
}

bool validEndpoints(const Graph& graph, bool hasStart, int start, bool hasTarget, int target) {

    if (!hasStart || !hasTarget) {
        cout << "Set both a start node and target node first.\n";
        return false;
    }

    if (!graph.hasNode(start) || !graph.hasNode(target)) {
        cout << "The start or target node no longer exists.\n";
        return false;
    }

    return true;
}

int main() {

    Graph graph;
    SearchResults bfs;
    SearchResults dfs;

    bool hasStart = false;
    bool hasTarget = false;

    int start = 0;
    int target = 0;

    bool running = true;

    while (running) {

        printMenu(graph, hasStart, start, hasTarget, target);

        int choice = getInteger("Enter your choice: ");

        switch (choice) {

            case 1:
                cout << "\nGraph Summary\n";
                cout << "Total nodes: " << graph.getNodeCount() << '\n';
                cout << "Total edges: " << graph.getEdgeCount() << '\n';
                bfs = BFS::search(graph, start, target);
                dfs = DFS::search(graph, start, target);
                GraphVisual::visualizeGraph(graph.getAdjacencyList(), bfs, dfs);
                break;

            case 2: {
                string path;
                cout << "Enter the file path: ";
                cin.ignore();
                getline(cin, path);
                ifstream file(path);
                if (!file.is_open()) {
                    cout << "Could not open file" << endl;
                    break;
                }
                string row;

                //loop
                while (getline(file, row)) {
                    stringstream ss(row);
                    string vertex;

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
                file.close();
                break;
            }

            case 3: {
                int node = getInteger("Enter node ID: ");

                if (graph.addNode(node))
                    cout << "Node added.\n";
                else
                    cout << "Node already exists.\n";

                break;
            }

            case 4: {
                int node = getInteger("Enter node ID to remove: ");

                if (graph.removeNode(node)) {
                    cout << "Node removed.\n";

                    if (hasStart && start == node) hasStart = false;
                    if (hasTarget && target == node) hasTarget = false;
                } else {
                    cout << "Node does not exist.\n";
                }

                break;
            }

            case 5: {
                int first = getInteger("Enter first node: ");
                int second = getInteger("Enter second node: ");

                if (graph.addEdge(first, second))
                    cout << "Edge added.\n";
                else
                    cout << "Could not add edge. Check both nodes.\n";

                break;
            }

            case 6: {
                int first = getInteger("Enter first node: ");
                int second = getInteger("Enter second node: ");

                if (graph.removeEdge(first, second))
                    cout << "Edge removed.\n";
                else
                    cout << "Edge does not exist.\n";

                break;
            }

            case 7: {
                int node = getInteger("Enter start node: ");

                if (graph.hasNode(node)) {
                    start = node;
                    hasStart = true;
                    cout << "Start node set.\n";
                } else {
                    cout << "Node does not exist. Add it first.\n";
                }

                break;
            }

            case 8: {
                int node = getInteger("Enter target node: ");

                if (graph.hasNode(node)) {
                    target = node;
                    hasTarget = true;
                    cout << "Target node set.\n";
                } else {
                    cout << "Node does not exist. Add it first.\n";
                }

                break;
            }

            case 9:
                if (validEndpoints(graph, hasStart, start, hasTarget, target)) {
                    printResults("BFS", BFS::search(graph, start, target));
                }
                break;

            case 10:
                if (validEndpoints(graph, hasStart, start, hasTarget, target)) {
                    printResults("DFS", DFS::search(graph, start, target));
                }
                break;

            case 11:
                if (validEndpoints(graph, hasStart, start, hasTarget, target)) {

                    bfs = BFS::search(graph, start, target);

                    dfs = DFS::search(graph, start, target);

                    printResults("BFS", bfs);
                    printResults("DFS", dfs);

                    cout << "\n========== COMPARISON ==========\n";

                    cout << "BFS runtime: " << bfs.runtimeMs << " ms\n";
                    cout << "DFS runtime: " << dfs.runtimeMs << " ms\n";

                    cout << "BFS nodes visited: " << bfs.nodesVisited << '\n';
                    cout << "DFS nodes visited: " << dfs.nodesVisited << '\n';

                    cout << "BFS edges examined: " << bfs.edgesExamined << '\n';
                    cout << "DFS edges examined: " << dfs.edgesExamined << '\n';

                    cout << "BFS path length: ";
                    if (bfs.found) cout << bfs.path.size() - 1;
                    else cout << "No path";

                    cout << "\nDFS path length: ";
                    if (dfs.found) cout << dfs.path.size() - 1;
                    else cout << "No path";

                    cout << '\n';
                }

                break;

            case 0:
                running = false;
                cout << "Exiting Graph Traversal Visualizer.\n";
                break;

            default:
                cout << "Invalid choice. Select 0 through 11.\n";
        }
    }

    return 0;
}
