//Final Project
#pragma once
#include "Graph.h"
#include "random.h"
#include "edge.h"
#include <vector>
#include <map>

using namespace std;

class MemeTracker : public Graph {
    public:
    //MemeTracker();
    void DFS(Vertex v);
    Graph & getGraph();

    private:
    map<Vertex, bool> visited;
    Graph _graph;
};