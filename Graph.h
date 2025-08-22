#pragma once
using namespace std;
#include <vector>
#include "Vertex.h"
#include <unordered_map>
class Graph{
public:

    /**
     * @brief init the graph to be empty
    */
    Graph() = default;

    /**
     * @brief add a vertex in the graph
     * @param lat - the lat of the new vertex
     * @param lon - the lon of the new vertex
     * @return return the idx the vertex is on
    */
    size_t AddVertex(const double& lat,const double &lon);

    /**
     * @brief return the vertex that found on index idx
    */
    Vertex& operator[](const size_t idx);

    /**
     * @brief add edge to the graph
     * @param v1 - the first vertex
     * @param v2 - the second vertex
    */
    void AddEdge(Vertex& v1, Vertex &v2,const size_t flags);

    ~Graph() = default;


private:
    /**
     * @brief return the edge of the graph
    */
    Edge* find_edge(const Vertex& v1,const Vertex& v2)const;
    vector<Vertex> vertexs;

};