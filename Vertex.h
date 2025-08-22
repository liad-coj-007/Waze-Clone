#pragma once
#include <deque>
using namespace std;



struct Edge{
   Vertex* vertex;
   Weight weight;
};

struct Vertex{
    //map to the graph
    
    int idx;// the idx of the vertex in the graph
    double lat, lon;
    //sorted list of edges
    deque<Edge> deque;
    /**
     * @brief build a vertex
    */
    Vertex(const double& lat, const double& lon);
};



class Weight{
};