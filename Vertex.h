#pragma once
#include <deque>
#include <cstddef>  // size_t
#include "Road.h"
#include "CompWeight.h"
class Vertex; // forward declaration
class Graph;

/**
 * @brief eq the vertexs 
 * @return true if v1 coordinates smaller than v2 coordinates
 */
bool operator<(const Vertex& v1, const Vertex& v2);

/**
 * @brief equal between two vertexs
 */
bool operator==(const Vertex& v1, const Vertex& v2);

struct Edge {
    Vertex* vertex;
    Road road;

    Edge(Vertex &v1, Vertex &v2, const size_t flags);
    double getWeight(const CompWeight& compweight) const;
};

struct Vertex {
    int idx;         // index in the graph
    double lat, lon;
    Graph* my_graph = nullptr;

    // edges sorted
    std::deque<Edge> in_edges;
    std::deque<Edge> out_edges;

    Vertex(const double& lat, const double& lon);
};
