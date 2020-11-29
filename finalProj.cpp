#include "finalProj.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include "Graph.h"
#include "edge.h"
using namespace std;


Graph & MemeTracker::getGraph(){
    return _graph;
}
void MemeTracker::DFS(Vertex v) {
    Graph & k = getGraph();
    k.DFS(v);
}