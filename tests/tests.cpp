#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include "../edge.h"
#include "../finalProj.h"
#include <vector>
#include <map>
#include <iostream>

TEST_CASE("Graph::getNumVertices returns the correct number of vertices") {
    Graph g(true, false);
    Vertex v1 = (Vertex)"1";

    g.insertVertex(v1);
    g.insertVertex("2");
    REQUIRE(g.getNumVertices() == 2);
}

TEST_CASE("Graph::DFS works") {
    Graph g1(true, false);
    /*
            b
         /     \
        a  -    c
       / \        \
       e  f         d
    */
    Vertex a = "a";
    Vertex b = "b";
    Vertex c = "c";
    Vertex d = "d";
    Vertex e = "e";
    Vertex f = "f";
    g1.insertVertex(a);
    g1.insertVertex(b);
    g1.insertVertex(c);
    g1.insertVertex(d);
    g1.insertVertex(e);
    g1.insertVertex(f);

    g1.insertEdge(b,a);
    g1.insertEdge(b,c);
    g1.insertEdge(c,d);
    g1.insertEdge(a,e);
    g1.insertEdge(a,f);
    g1.insertEdge(a,c);

    REQUIRE(g1.getNumVertices() == 6);

    REQUIRE(g1.IDDFS(b, c, 1) == true);
    REQUIRE(g1.IDDFS(b, d, 1) == false);
    REQUIRE(g1.IDDFS(b, c, 2) == true);


}

TEST_CASE("Prim MST test") {
    
    Graph g1(true, false);
    /*
            b
         2/   \4
        a  -5    c
      1 / \3       \7
       e  f         d
    */
    Vertex a = "a";
    Vertex b = "b";
    Vertex c = "c";
    Vertex d = "d";
    Vertex e = "e";
    Vertex f = "f";
    g1.insertVertex(a);
    g1.insertVertex(b);
    g1.insertVertex(c);
    g1.insertVertex(d);
    g1.insertVertex(e);
    g1.insertVertex(f);

    g1.insertEdge(b,a);
    g1.setEdgeWeight(b, a, 2);
    g1.insertEdge(b,c);
    g1.setEdgeWeight(b, c, 4);
    g1.insertEdge(c,d);
    g1.setEdgeWeight(c, d, 7);
    g1.insertEdge(a,e);
    g1.setEdgeWeight(a, e, 1);
    g1.insertEdge(a,f);
    g1.setEdgeWeight(a, f, 3);
    g1.insertEdge(a,c);
    g1.setEdgeWeight(a, c, 5);
    //cout << "Checkpoint 1" << endl;
    Graph k(true, false);
    MemeTracker mt(g1);
    //cout << "Checkpoint 2" << endl;
    //Graph testGraph = mt.PrimMST(g1, e);
    g1.PrimMST1(e);
    //cout << "Checkpoint 3" << endl;

    // REQUIRE(testGraph.vertexExists(a));
    // REQUIRE(testGraph.vertexExists(b));
    // REQUIRE(testGraph.vertexExists(c));
    // REQUIRE(testGraph.vertexExists(d));
    // REQUIRE(testGraph.vertexExists(e));
    // REQUIRE(testGraph.vertexExists(f));

    REQUIRE(g1.vertexExists(a));
    REQUIRE(g1.vertexExists(b));
    REQUIRE(g1.vertexExists(c));
    REQUIRE(g1.vertexExists(d));
    REQUIRE(g1.vertexExists(e));
    REQUIRE(g1.vertexExists(f));






}




