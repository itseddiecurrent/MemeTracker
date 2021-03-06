//Code from lab_ml
#include "Graph.h"
#include <map>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;



const Vertex Graph::InvalidVertex = "_INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(bool weighted) : weighted(weighted),directed(false),random(Random(0))
{
}

Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed),random(Random(0))
{
}

Graph::Graph(bool weighted, int numVertices, unsigned long seed)
    :weighted(weighted),
      directed(false),
     random(Random(seed)) 
{
    if (numVertices < 2)
    {
     error("numVertices too low");
     exit(1);
    }

    vector<Vertex> vertices;
    for (int i = 0; i < numVertices; i++)
    {
        insertVertex(to_string(i));
        vertices.push_back(to_string(i));
    }

    // make sure all vertices are connected
    random.shuffle(vertices);
    Vertex cur = vertices[0];
    for (size_t i = 0; i < vertices.size() - 1; ++i)
    {
        Vertex next = vertices[i + 1];
        insertEdge(cur, next);
        if (weighted) 
        {
            int weight = random.nextInt();
            setEdgeWeight(cur, next, weight);
        }
        cur = next;
    }

    // keep the graph from being overpopulated with edges,
    //  while still maintaining a little randomness
    int numFailures = 0;
    int idx = 0;
    random.shuffle(vertices);
    while (numFailures < 2) 
    {
        if (!insertEdge(vertices[idx], vertices[idx + 1])) 
        {
            ++numFailures;
        } 
        else 
        {
            // if insertEdge() succeeded...
            if (weighted)
                setEdgeWeight(vertices[idx], vertices[idx + 1],
                              random.nextInt());
            ++idx;
            if (idx >= numVertices - 2) 
            {
                idx = 0;
                random.shuffle(vertices);
            }
        }
    }
}

vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

int Graph::getNumVertices() const {
    vector<Vertex> ver = getVertices();
    return ver.size();
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
                if(!directed)
                {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        adjacency_list[destination][source] = new_edge_reverse;
    }
    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
}

int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v); 
            }
            adjacency_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exit
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>();
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);
    if(!directed)
    {
        if(adjacency_list.find(destination)== adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, Edge>();
        }
        adjacency_list[destination][source] = Edge(source, destination);
    }
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        adjacency_list[destination].erase(source);
    }
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;

    if(!directed)
        {
            Edge new_edge_reverse(destination,source, weight, e.getLabel());
            adjacency_list[destination][source] = new_edge_reverse;
        }

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination + " -> " + source);
            return false;
        }
    }
    return true;
}

bool Graph::isDirected() const
{
    return directed;
}

void Graph::clear()
{
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot()
{
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;
            if (weighted)
                cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"1300\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"7.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    vector<Vertex> allv = getVertices();
    //lambda expression
    sort(allv.begin(), allv.end(), [](const Vertex& lhs, const Vertex& rhs) {
        return stoi(lhs.substr(3)) > stoi(rhs.substr(3));
    });

    int xpos1 = 100;
    int xpos2 = 100;
    int xpos, ypos;
    for (auto it : allv) {
        string current = it;
        neatoFile 
            << "\t\"" 
            << current
            << "\"";
        if (current[1] == '1') {
            ypos = 100;
            xpos = xpos1;
            xpos1 += 100;
        }
        else {
            ypos = 200;
            xpos = xpos2;
            xpos2 += 100;
        }
        neatoFile << "[pos=\""<< xpos << "," << ypos <<"\"]";
        neatoFile << ";\n";
    }

    neatoFile << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            string vertex1Text = it->first;
            string vertex2Text = it2->first;

            neatoFile << "\t\"" ;
            neatoFile << vertex1Text;
            neatoFile << "\" -- \"" ;
            neatoFile << vertex2Text;
            neatoFile << "\"";

            string edgeLabel = it2->second.getLabel();
            if (edgeLabel == "WIN") {
                neatoFile << "[color=\"blue\"]";
            } else if (edgeLabel == "LOSE") {
                neatoFile << "[color=\"red\"]";                
            } else {
                neatoFile << "[color=\"grey\"]";
            }
            if (weighted && it2->second.getWeight() != -1)
                neatoFile << "[label=\"" << it2->second.getWeight() << "\"]";
            
            neatoFile<< "[constraint = \"false\"]" << ";\n";
        }
    }

    neatoFile << "}";
    neatoFile.close();
    string command = "neato -n -Tpng " + filename + " -o " + "images/" + title
                     + ".png 2> /dev/null";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}


/*  The recursive Depth First Search on Graph
    @param v The starting vertex for the DFS
*/
vector<Vertex> Graph::DFS(Vertex v) {
    visited[v] = true;
    //Push v into vector.
    output.push_back(v);
    for (Vertex i : getAdjacent(v)) {
        if (visited[i] == false) {
            DFS(i);
        }
    }
    return output;
}

/* Recursive function for Iterative Deepening Depth First search, A Depth Limited 
    Search from a given source to a given target within a given limit
    @param 
    source: the source Vertex for the search
    target: the target Vertex for the search
    limit: the depth limit 
    @return: true if the target is reached within the limit, false otherwise

*/
bool Graph::DLS(Vertex source, Vertex target, int limit) {
    if (source == target) {
        return true;
    }
    if (limit <= 0) {
        return false;
    }
    for (Vertex i : getAdjacent(source)) {
        if (DLS(i, target, limit-1) == true) {
            return true;
        }
    }
    return false;
}

/* Iterative Deepening Depth First Search, returns true if the target is reached.
    @param 
    source: the source Vertex for the search
    target: the target Vertex for the search
    limit: the depth limit 
    @return: true if the target is reachable within the limit, false otherwise

*/
bool Graph::IDDFS(Vertex source, Vertex target, int max_depth) {
    for (int i = 0; i <= max_depth; i++) {
        if (DLS(source, target, i) == true) {
            return true;
        }
    }
    return false;
}

/*Prim's (also known as Jarník's) algorithm is a greedy algorithm 
that finds a minimum spanning tree for a weighted undirected graph. 
This means it finds a subset of the edges that forms a tree that includes 
every vertex, where the total weight of all the edges in the tree is minimized. 

@param start: the starting Vertex as the source node of the MST.
The function removes edges that not in the Minimum Spanning Tree from the graph.
*/
void Graph::PrimMST1(Vertex start){
    
   priority_queue<pair<int, Vertex>, vector<pair<int, Vertex>>, greater<pair<int, Vertex>>> pq; 
  
    // Taking vertex 0 as source 
    // Create a vector for keys and initialize all 
    // keys as infinite (INF) 
    map<Vertex,int> key;
    for (Vertex k : getVertices()) {
        key[k] = (int)INFINITY;
    } 
    // To store parent array which in turn store MST 
    map<Vertex,Vertex> parent;
    for (Vertex k : getVertices()) {
        parent[k] = "";
    } 
    // To keep track of vertices included in MST 
    map<Vertex, bool> inMST; 
    for (Vertex k: getVertices()) {
        inMST[k] = false;
    } 
    // Insert source itself in priority queue and initialize 
    // its key as 0. 
    pq.push(make_pair(0, start)); 
    key[start] = 0; 
    /* Looping till priority queue becomes empty */
    while (!pq.empty()) 
    { 
        // The first vertex in pair is the minimum key 
        // vertex, extract it from priority queue. 
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted key (key must be first item 
        // in pair) 
        Vertex u = pq.top().second; 
        pq.pop(); 
        inMST[u] = true;  // Include vertex in MST 
        // 'i' is used to get all adjacent vertices of a vertex 
        for (Vertex v : getAdjacent(u)) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            //  If v is not in MST and weight of (u,v) is smaller 
            // than current key of v 
            if (inMST[v] == false && key[v] > getEdgeWeight(u, v)) 
            { 
                // Updating key of v 
                key[v] = getEdgeWeight(u, v); 
                pq.push(make_pair(key[v], v)); 
                parent[v] = u; 
                Vertex temp = u;
            }
        } 
    } 

    Graph T(true, false);
    for (Vertex v : getVertices()) {
        T.insertVertex(v);
    }
    for (pair<Vertex, Vertex> it : parent) {
            T.insertEdge(it.first,it.second);
            if (this->edgeExists(it.first, it.second)) {
            T.setEdgeWeight(it.first, it.second, getEdgeWeight(it.first, it.second));
            }
    }
    *this = T;
  
}





