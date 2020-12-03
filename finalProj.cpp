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
    std::priority_queue<Vertex> q;
    q.push(start);
    //fib.insert(start);
    vector<Vertex> vers = g.getVertices();
    int size = g.getNumVertices();
    map<Vertex, bool> added;
    map<Vertex, int> distance;
    //Initialization
    for (Vertex vi : vers) {
        added[vi] = false;
        distance[vi] = (int)INFINITY;
        //fib.insert(vi);
        q.push(start);
    }
    distance[start] = 0;


    
    return g;
    

}
