
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
    //Smaller case
    Graph memeGraph(true, false);
    vector<string> lines = file_to_vector("memeset.txt");
    vector<string> copy = lines;
    for (string line: lines) {
        //Get all vertices inserted
        if (line.at(0) == 'P') {
            line.erase(0,1);
            memeGraph.insertVertex((Vertex)line);
        }
        //Search for linked directories
        if (line.at(0) == 'L') {
            //Check in any of the L line happen to be one of our vertices, and if that is the case
            //we are inserting an edge between the parent P of the L and the L itself. 
            string copyLine = line;
            line.erase(0,1);
            size_t pindex;
            if (memeGraph.vertexExists((Vertex)line)) {
                for (size_t i = 0; i < copy.size(); i++) {
                    if (copy[i] == copyLine) {
                        while (copy[i].at(0) != 'P') {
                            i--;
                        }
                    }
                    pindex = i;
                }
                memeGraph.insertEdge((Vertex)lines[pindex], (Vertex)line);
                memeGraph.setEdgeWeight((Vertex)lines[pindex], (Vertex)line, 0);
            }
        }
    }

    //Bigger case
    Graph memeGraph1(true, true);
    vector<string> lines1 = file_to_vector("400000line.txt");
    vector<string> copy1 = lines1;
    for (string line: lines1) {
        //Get all vertices inserted
        if (line.at(0) == 'P') {
            line.erase(0,1);
            memeGraph.insertVertex((Vertex)line);
        }
        //Search for linked directories
        if (line.at(0) == 'L') {
            string copyLine = line;
            line.erase(0,1);
            size_t pindex;
            if (memeGraph.vertexExists((Vertex)line)) {
                for (size_t i = 0; i < copy.size(); i++) {
                    if (copy[i] == copyLine) {
                        while (copy[i].at(0) != 'P') {
                            i--;
                        }
                    }
                    pindex = i;
                }
                memeGraph.insertEdge((Vertex)lines1[pindex], (Vertex)line);
                memeGraph.setEdgeWeight((Vertex)lines1[pindex], (Vertex)line, 0);
            }
        }
    }

    return 1;
}