#pragma once

#include <deque>

class Vertex; // forward declaration

class Weight {
    // TODO: add weight logic
};

struct Edge {
    Vertex* vertex;
    Weight weight;
};

struct Vertex {
    int idx;         // the idx of the vertex in the graph
    double lat, lon;
    
    // sorted list of edges
    std::deque<Edge> edges;

    /**
     * @brief Build a vertex
     */
    Vertex(const double& lat, const double& lon);
};
