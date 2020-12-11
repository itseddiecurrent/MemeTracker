
#include "Graph.h"
#include "finalProj.h"
#include "random.h"
#include "edge.h"
#include "readFromFile.hpp"



#include <cstring>
#include <vector>
#include <stdio.h>
#include <exception>
#include <list>
#include <unordered_map>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
//#include <graphviz>


using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;
using namespace std;


int main() {
// Graph memeGraph1(true, false);
//     vector<string> lines1 = file_to_vector("400000line.txt");
//     vector<string> copy1 = lines1;
//     for (string line: lines1) {
//         //Get all vertices inserted
//         if (line.at(0) == 'P') {
//             line.erase(0,1);
//             memeGraph.insertVertex((Vertex)line);
//         }

    Graph g1(true, false);
    cout << "Point 0" << endl;

    vector<string> smallFileVector = file_to_vector("100line.txt");
    cout << "Point 1" << endl;
    // for (string i : smallFileVector) {
    //     cout << i << endl;
    // }

    for (size_t i = 0; i < smallFileVector.size() - 1; i++) {
        //Insert "P" strings as vertices 
        Vertex temp;
        if (smallFileVector[i].at(0) == 'P') {
            //cout << smallFileVector[i + 1] << endl;
            g1.insertVertex(smallFileVector[i + 1]);
        }
    }
    cout << "Point 2" << endl;
        //Connect all vertices
    for (size_t i = 0; i < smallFileVector.size(); i++) {
        for (size_t j = 0; j < smallFileVector.size(); j++) {
            Vertex v1 = (Vertex)smallFileVector[i];
            Vertex v2 = (Vertex)smallFileVector[j];
            //cout << "Point 3" << endl;
            //Insert edges and set initial edge weight
            int startWeight = g1.getNumVertices();
            if (i != j && g1.vertexExists(v1) && g1.vertexExists(v2) && g1.edgeExists(v1, v2) == false) {
                g1.insertEdge(v1, v2);
                g1.setEdgeWeight(v1, v2, startWeight);
            } 

            //cout << "Point 4" << endl;
            //Decrease edge weight for edges with same timestamps
            if (i < smallFileVector.size() - 2 && j < smallFileVector.size()-2){
            if (i != j) {
                map <Edge, bool> visited;
                for (Edge e : g1.getEdges()) {
                    visited[e] = false;
                }
                if (g1.edgeExists(v1, v2)&&!visited[g1.getEdge(v1,v2)]) {
                if (smallFileVector[i+2] == smallFileVector[j+2]) {
                    int currentWeight = g1.getEdgeWeight(v1, v2);
                   if (g1.vertexExists(v1) && g1.vertexExists(v2)) {
                            g1.setEdgeWeight(v1, v2, currentWeight--);
                            cout << v1 << endl;
                            visited[g1.getEdge(v1,v2)] = true;
                            visited[g1.getEdge(v2,v1)] = true;
                       
                   }
                }
                }
            }
           
            }
            //cout << "Point 5" << endl;
        }

    }
    g1.PrimMST1(g1.getVertices()[0]);
    vector<Vertex> dfs_vector = g1.DFS(g1.getVertices()[0]);
    cout << "got here" << endl;
    for (Vertex v1 : dfs_vector) {
        for (Vertex v2 : dfs_vector) {
            cout << "in loop here" << endl;
            for (int p = dfs_vector.size(); p > 0; p--) {
                if (v1 != v2 && g1.IDDFS(v1, v2, p)) {
                    if (g1.IDDFS(v1, v2, p-1) == false) {
                        cout << v1 << " and " << v2 << " has correlations within " << to_string(p) << " entries." << endl;
                    }
                }
            }
        }
    }

    //g1.print();
    //cout << "Point 6" << endl;



    //g1.PrimMST1()
   
 
}