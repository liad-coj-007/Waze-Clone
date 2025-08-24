#pragma once
#include <deque>
#include <cstddef>  // מגדיר size_t
#include "CompWeight.h"
#include "Road.h"
class Vertex; // forward declaration
class Graph;




/**
 * @brief eq the vertexs 
 * @return true if v1 cordinates smaller then v2 cordinates
*/
bool operator<(const Vertex& v1,const Vertex &v2);

/**
 * @brief equal between two vertexs
*/
bool operator==(const Vertex& v1,const Vertex& v2);

struct Edge {
    Vertex* vertex;
    Road road;
    Edge(Vertex &v1,Vertex &v2,const size_t flags);
};






struct Vertex {
    int idx;         // the idx of the vertex in the graph
    double lat, lon;
    Graph* my_graph;
    // sorted list of edges
    std::deque<Edge> in_edges;
    std::deque<Edge> out_edges;
    /**
     * @brief Build a vertex
     */
    Vertex(const double& lat, const double& lon);
};



