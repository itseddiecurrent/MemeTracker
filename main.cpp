
#include "Graph.h"
#include "finalProj.h"
#include "random.h"
#include "edge.h"
#include "readFromFile.hpp"
#include <fstream> 
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
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

    Graph g(true, false);
    Vertex one = "1";
    g.insertVertex(one);
    g.PrimMST1(one);
}