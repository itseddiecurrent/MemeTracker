#include "finalProj.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <cmath>
#include "Graph.h"
#include "edge.h"
//#include "fibheap.h"
using namespace std;

MemeTracker::MemeTracker() {
    //_graph = new Graph(true, false);
}

MemeTracker::MemeTracker(Graph f) {
    _graph = f;
}

Graph & MemeTracker::getGraph(){
    return _graph;
}
void MemeTracker::DFS(Vertex v) {
    Graph & k = getGraph();
    k.DFS(v);
}
Graph MemeTracker::PrimMST(Graph g, Vertex start){
    //FibonacciHeap fib;
    map<Vertex, int> dist;
    map<Vertex, Vertex> previous;
    for (Vertex v : g.getVertices()) {
        dist[v] = (int)INFINITY;
        previous[v] = (Vertex)NULL;
    }
    dist[start] = 0;

    std::priority_queue<Vertex> q;
    for (Vertex v : g.getVertices()) {
        q.push(v);
    }
    Graph T(true, false);
    while(!q.empty()) {
        Vertex m = q.top();
        T.insertVertex(m);
        T.insertEdge(m, previous[m]);
        for (Vertex v : g.getAdjacent(m)) {
            if (!T.vertexExists(v)) {
                if (g.getEdgeWeight(m,v) < dist[v]) {
                    dist[v] = g.getEdgeWeight(m,v);
                    previous[v] = m;
                }
            }
        }
    }
    return T;
}


bool MemeTracker::DLS(Vertex source, Vertex target, int limit) {
    if (source == target) {
        return true;
    }
    if (limit <= 0) {
        return false;
    }
    Graph & k = getGraph();
    for (auto i = k.getAdjacent(source).begin(); i != k.getAdjacent(source).end(); i++) {
        if (DLS(*i, target, limit-1) == true) {
            return true;
        }
    }
    return false;
}

bool MemeTracker::IDDFS(Vertex source, Vertex target, int max_depth) {
    for (int i = 0; i <= max_depth; i++) {
        if (DLS(source, target, i) == true) {
            return true;
        }
    }
    return false;
}