#pragma once

#include "Vertex.h"
#include <unordered_map>
using namespace std;

struct VertexHash{
    /**
     * @brief hash function for vertex
    */
    std::size_t operator()(const Vertex& v)const;
};

struct Dist{

    /**
     * @brief build a dist function for vertex
     * @param vertex - the vertex we use
    */
    Dist(Vertex* vertex);

    /**
     * @brief defualt constractor
    */
    Dist();

    /**
     * @brief set dist 
    */
    void SetDist(const double &dist);

    /**
     * @brief if we found dist smaller we fix the dist to be dist
     * else we don't
    */
    bool FixDist(const double &dist);

    /**
     * @brief init the dist to zero
    */
    void Init();
    /**
     * @brief build a dist for route that start from
     * other -> edge -> me
    */
    Dist BuildFixDist(Dist& other,const Edge& edge,
    Vertex& to,const CompWeight& compweight);


public:
    Vertex* vertex;
    bool is_inf;
    double totaldist;
    double huristic;
    size_t heap_idx;
    bool is_on_heap;

};

/**
 * @brief return true if d1 < d2
*/
bool operator<(const Dist& d1,const Dist& d2);


class DistFunction{
public:
    DistFunction() = default;
    /**
     * @brief get the dist of vertex if it don't exist create a new one
     * and return it
     * @return the dist of the vertex
    */
    Dist& operator[]( Vertex &vertex);
private:
    unordered_map<Vertex,Dist,VertexHash> map;
};