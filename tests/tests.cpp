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

TEST_CASE("Iterative Deepening DFS Test") {
    Graph g1(true, false);
    /*
            b
         /     \
        a  -    c
       / \        \
      e   f        d

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
    REQUIRE(g1.IDDFS(b, c, 2) == true);

    REQUIRE(g1.IDDFS(b, d, 2) == true);
    REQUIRE(g1.IDDFS(b, d, 1) == false);

    REQUIRE(g1.IDDFS(b, e, 3) == true);
    REQUIRE(g1.IDDFS(b, e, 4) == true);

    REQUIRE(g1.IDDFS(c, f, 2) == true);
    REQUIRE(g1.IDDFS(c, f, 1) == false);
}

TEST_CASE("Basic PrimMST Test") {
    Graph g(true, false);
    Vertex one = "1";
    g.insertVertex(one);
    g.PrimMST1(one);
    REQUIRE(g.vertexExists(one));
}

TEST_CASE("PrimMST Test 1") {
    
    Graph g1(true, false);
    
    /*
    X marks deleted edge
          BEFORE

            b
         2/   \4
        a  --5--c
      1 / \3      \7
       e  f         d

           AFTER

             b
          2/   \4
         a  XXXX  c
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
    g1.insertEdge(e, a);
    g1.setEdgeWeight(e, a, 1);
    g1.insertEdge(a,f);
    g1.setEdgeWeight(a, f, 3);
    g1.insertEdge(a,c);
    g1.setEdgeWeight(a, c, 5);

    Graph k(true, false);
    MemeTracker mt(g1);
    g1.PrimMST1(e);
    
    REQUIRE(g1.vertexExists(a));
    REQUIRE(g1.vertexExists(b));
    REQUIRE(g1.vertexExists(c));
    REQUIRE(g1.vertexExists(d));
    REQUIRE(g1.vertexExists(e));
    REQUIRE(g1.vertexExists(f));

    REQUIRE(g1.edgeExists(b, a));
    REQUIRE(g1.edgeExists(b, c));
    REQUIRE(g1.edgeExists(c, d));
    REQUIRE(g1.edgeExists(e, a));
    REQUIRE(g1.edgeExists(a, f));
    REQUIRE(g1.edgeExists(a, c) == false);
}

TEST_CASE("Prim MST Test 2") {
    
    Graph g1(true, false);
    /*
    X marks deleted edge
           BEFORE

               3    2   
           c  -- b - f
        2/  4\       | 8
        a --  d      e  
           1  


           AFTER

              3    2   
           c  -- b - f
        2/   X       | 8
        a --  d      e  
           1  
           
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

    g1.insertEdge(c,a);
    g1.setEdgeWeight(c, a, 2);
    g1.insertEdge(c,d);
    g1.setEdgeWeight(c, d, 4);
    g1.insertEdge(a,d);
    g1.setEdgeWeight(a, d, 1);
    g1.insertEdge(c,b);
    g1.setEdgeWeight(c, b, 3);
    g1.insertEdge(b,f);
    g1.setEdgeWeight(b, f, 2);
    g1.insertEdge(f,e);
    g1.setEdgeWeight(f, e, 8);
    
    Graph k(true, false);
    MemeTracker mt(g1);
    g1.PrimMST1(c);
    
    REQUIRE(g1.vertexExists(a));
    REQUIRE(g1.vertexExists(b));
    REQUIRE(g1.vertexExists(c));
    REQUIRE(g1.vertexExists(d));
    REQUIRE(g1.vertexExists(e));
    REQUIRE(g1.vertexExists(f));

    REQUIRE(g1.edgeExists(a,c));
    REQUIRE(g1.edgeExists(a,d));
    REQUIRE(g1.edgeExists(c,b));
    REQUIRE(g1.edgeExists(b,f));
    REQUIRE(g1.edgeExists(f,e));
    REQUIRE(g1.edgeExists(c,d) == false);
}

TEST_CASE("PrimMST + Iterative Deepening Test") {
     Graph g1(true, false);
    /*
    X marks deleted edge
           BEFORE

               3    2   
           c  -- b - f
        2/  4\       | 8
        a --  d      e  
           1  


           AFTER

              3    2   
           c  -- b - f
        2/   X       | 8
        a --  d      e  
           1  
           
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

    g1.insertEdge(c,a);
    g1.setEdgeWeight(c, a, 2);
    g1.insertEdge(c,d);
    g1.setEdgeWeight(c, d, 4);
    g1.insertEdge(a,d);
    g1.setEdgeWeight(a, d, 1);
    g1.insertEdge(c,b);
    g1.setEdgeWeight(c, b, 3);
    g1.insertEdge(b,f);
    g1.setEdgeWeight(b, f, 2);
    g1.insertEdge(f,e);
    g1.setEdgeWeight(f, e, 8);

    // BEFORE PRIMMST - IDDFS TEST
    REQUIRE(g1.IDDFS(b, c, 1) == true);
    REQUIRE(g1.IDDFS(b, c, 2) == true);

    REQUIRE(g1.IDDFS(b, d, 3) == true);
    REQUIRE(g1.IDDFS(b, d, 2) == true);
    REQUIRE(g1.IDDFS(b, d, 1) == false);

    REQUIRE(g1.IDDFS(b, e, 3) == true);
    REQUIRE(g1.IDDFS(b, e, 4) == true);

    REQUIRE(g1.IDDFS(c, f, 3) == true);
    REQUIRE(g1.IDDFS(c, f, 1) == false);

    Graph k(true, false);
    MemeTracker mt(g1);
    g1.PrimMST1(c);

    // AFTER PRIMMST - IDDFS TEST
    REQUIRE(g1.IDDFS(b, c, 1) == true);
    REQUIRE(g1.IDDFS(b, c, 2) == true);

    REQUIRE(g1.IDDFS(b, d, 4) == true);
    REQUIRE(g1.IDDFS(b, d, 3) == true);
    REQUIRE(g1.IDDFS(b, d, 1) == false);

    REQUIRE(g1.IDDFS(b, e, 3) == true);
    REQUIRE(g1.IDDFS(b, e, 4) == true);

    REQUIRE(g1.IDDFS(c, f, 3) == true);
    REQUIRE(g1.IDDFS(c, f, 1) == false);
}

TEST_CASE("DFS Traversal Test") {
Graph g1(true, false);
    /*
            b
         /     \
        a       c
       / \        \
      e   f        d

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

    vector<Vertex> correctTraversal{b,c,d,a,f,e};
    vector<Vertex> resultTraversal = g1.DFS(b);
    REQUIRE(g1.getNumVertices() == 6);
    REQUIRE(resultTraversal == correctTraversal);
}




