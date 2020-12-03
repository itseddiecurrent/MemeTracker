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
    //MemeTracker(Graph g);
    
    void DFS(Vertex v);
    Graph & getGraph();
    Graph PrimMST(Graph g, Vertex start);

    private:
    map<Vertex, bool> visited;
    Graph _graph;

};