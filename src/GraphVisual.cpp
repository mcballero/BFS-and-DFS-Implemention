#include <iostream>
#include <string>
#include <vector>
#include "GraphVisual.h"
#include "SearchResults.h"
#include "Bridges.h"
#include "GraphAdjList.h"
#include "DataSource.h"

using namespace std;
using namespace bridges;

//the BRIDGES bacon number template was used as a starting template for this visualizer

void GraphVisual::convertGraph(std::unordered_map<int, std::vector<int>> &graph, GraphAdjList<int, int> *convertedGraph) {
  //vars to control positioning
  double originX = 200, originY = 200;
  double radius = 100;
  int n = 0;
  int perim = 5;

  //convert vertices
  for (const auto &itr : graph) {
    int vertex = itr.first;
    double angleRad = n*(2*M_PI/perim);
    double vertexX = originX + cos(angleRad)*radius;
    double vertexY = originY + sin(angleRad)*radius;

    convertedGraph->addVertex(vertex);
    convertedGraph->getVertex(vertex)->setLabel(to_string(vertex));
    convertedGraph->getVertex(vertex)->setColor(Color("black"));
    convertedGraph->getVertex(vertex)->setLocation(vertexX, vertexY);
    n++;
    if (n%perim == 0) {
      perim = perim*2-1;
      radius = radius*1.2+200;
      n = 0;
    }
  }

  //convert edges
  for (const auto &itr : graph) {
    int from = itr.first;
    //loop through neighbors
    for (int to : itr.second) {
      convertedGraph->addEdge(from, to);
      convertedGraph->getLinkVisualizer(from, to)->setColor(Color("grey"));
      convertedGraph->getLinkVisualizer(from, to)->setThickness(0.5);
    }
  }
}

void GraphVisual::visualizeGraph(std::unordered_map<int, std::vector<int>> graph, SearchResults &resultsBFS, SearchResults &resultsDFS) {
  //initialize BRIDGES
  Bridges bridges(1, "CountMakkula", "1010610796120");
  bridges.setTitle("DFS vs BFS");
  bridges.setDescription("Shows the difference between a DFS and a BFS for two given nodes.\nBFS = Blue.   \nDFS = Green.   \nBoth BFS & DFS = Red.   \nStart/end = Purple.");

  //set up and convert graph
  GraphAdjList<int> bridgesGraph;
  convertGraph(graph, &bridgesGraph);
  int graphSize = graph.size();
  double lineWeight = 3.0;
  if (graphSize >= 1000) {
    lineWeight = 10.0;
  }

  //BFS
  //if the search was successful, print out the path
  if (resultsBFS.found) {
    const std::vector<int> &path = resultsBFS.path;
    for (int i = 1; i < path.size(); i++) {
      int vertex = path[i-1];
      bridgesGraph.getVisualizer(vertex)->setColor(Color("blue"));
      bridgesGraph.getVisualizer(vertex)->setSize(30.0);

      bridgesGraph.getLinkVisualizer(vertex, path[i])->setColor(Color("blue"));
      bridgesGraph.getLinkVisualizer(vertex, path[i])->setThickness(lineWeight);
    }
  }

  //DFS
  //if the search was successful, print out the path
  if (resultsDFS.found) {
    const std::vector<int> &path = resultsDFS.path;
    for (int i = 1; i < path.size(); i++) {
      int vertex = path[i-1];
      //if this vertex already visited by BFS, color it red
      if(bridgesGraph.getVisualizer(vertex)->getColor() == Color("blue")) {
        bridgesGraph.getVisualizer(vertex)->setColor(Color("red"));
        bridgesGraph.getVisualizer(vertex)->setSize(40.0);

        //if next vertex also visited by BFS, color path to it red
        //if (bridgesGraph.getVisualizer(path[i])->getColor() == Color("blue")) {
        if (bridgesGraph.getLinkVisualizer(vertex, path[i])->getColor() == Color("blue")) {
          bridgesGraph.getLinkVisualizer(vertex, path[i])->setColor(Color("red"));
          bridgesGraph.getLinkVisualizer(vertex, path[i])->setThickness(lineWeight);
        }else {
          bridgesGraph.getLinkVisualizer(vertex, path[i])->setColor(Color("green"));
          bridgesGraph.getLinkVisualizer(vertex, path[i])->setThickness(lineWeight);
        }
      }else {//color vertex and path green otherwise
        bridgesGraph.getVisualizer(vertex)->setColor(Color("green"));
        bridgesGraph.getVisualizer(vertex)->setSize(30.0);

        bridgesGraph.getLinkVisualizer(vertex, path[i])->setColor(Color("green"));
        bridgesGraph.getLinkVisualizer(vertex, path[i])->setThickness(lineWeight);
      }
    }
    //color start and end purple
    bridgesGraph.getVisualizer(path[0])->setColor(Color("purple"));
    bridgesGraph.getVisualizer(path[0])->setShape(SQUARE);
    bridgesGraph.getVisualizer(path[path.size()-1])->setColor(Color("purple"));
    bridgesGraph.getVisualizer(path[path.size()-1])->setShape(STAR);
  }

  //generate visual
  bridges.setDataStructure(&bridgesGraph);
  bridges.visualize();
}
