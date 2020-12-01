#include "finalProj.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include "Graph.h"
#include "edge.h"
#include "fibheap.h"
using namespace std;

MemeTracker::MemeTracker(Graph g) {
    _graph = g;
    vector<Vertex> vertices = g.getVertices();
    for (Vertex v : vertices) {
        visited.insert(make_pair<Vertex, bool>(v, false));
    }
}


Graph & MemeTracker::getGraph(){
    return _graph;
}
void MemeTracker::DFS(Vertex v) {
    Graph & k = getGraph();
    k.DFS(v);
}
Graph & MemeTracker::PrimMST(Graph g, Vertex start) {
    priority_queue<int, Vertex> prq;
    
    prq.push(make_pair<int, Vertex>(0, start));
    int size = g.getNumVertices();
    vector<bool> added;
    added.resize(size, false);
    int mst_cost = 0;
    Graph T;
    while (!prq.empty()) {

    }
}
