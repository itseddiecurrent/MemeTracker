#include "catch.hpp"
#include "Graph.h"
#include "edge.h"
#include <vector>
#include <map>
#include <iostream>

TEST_CASE("Graph::getNumVertices returns the correct number of vertices") {
    Graph g(true, true);
    Vertex v1 = (Vertex)"1";

    g.insertVertex(v1);
    g.insertVertex("2");
    REQUIRE(g.getNumVertices() == 2);
}

