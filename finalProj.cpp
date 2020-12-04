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

/*MemeTracker::MemeTracker() {
    
    vector<Vertex> vertices = g.getVertices();
    for (Vertex v : vertices) {
        visited.insert(make_pair<Vertex, bool>(v, false));
    }
}*/


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
    Graph T(true, true);
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
