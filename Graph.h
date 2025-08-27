#pragma once
using namespace std;
#include <vector>
#include "Vertex.h"
#include "Dist.h"
#include "Heap.h"
#include "DistFunc.h"




struct Path{
    std::deque<Edge> edges;
    Dist dist;
    Path(DistFunction& distfunc,Vertex& vertex);
    bool is_inf()const;
    size_t size()const;
};

class Graph{
public:

    /**
     * @brief init the graph to be empty
    */
    Graph() = default;

    /**
     * @brief build a graph with
     * size vertexs
    */
    Graph(const size_t size);

    /**
     * @brief return the size of the 
     * graph
    */
    size_t size()const;

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

    /**
     * @brief do A star algo to find the dist function
     * @param from the vertex we start from
     * @param to the vertex we want to go
     * @return the distfunction we found
    */
    DistFunction AStar( Vertex &from , Vertex &to,const CompWeight& compweight);

    /**
     * @brief find the optimal path from vertex from to dest
     * @param from - the vertex we start from
     * @param dest - the vertex we finish from
    */
    Path find_route( Vertex& from, Vertex &dest,const CompWeight& comp);



private:

    /**
     * @brief return the edge of the graph
    */
    Edge* find_edge( Vertex& v1, Vertex& v2)const;

    int find_edge(const vector<Edge>& edges,const Vertex& v2)const;
    /**
     * @brief find the next vertex on the road
    */
    Edge& find_next_vertex(Vertex &v,DistFunction& distfunc,
    const CompWeight& compweight);

    /**
     * @brief find the edge base on vertex
    */
    Edge* find_edge(const Vertex& vertex, vector<Edge>& edges);

    /**
     * @brief add edge to the deque
     * @param old_edges - edges list we want to add to
     * @param edge - the edge we add
    */
    void AddEdge(vector<Edge>& old_edges,Edge edge);

   

    /**
     * @brief init the data stuctre
     * for A^* algo
    */
    void InitAStar(Heap& heap,Vertex &from,DistFunction& distfunc);

    /**
     * @brief fix the distfunction for all vertexs we found
     * a route to
    */
    void FixDist(Dist*& dist,Heap& heap,DistFunction& distfunc,
    const CompWeight& compweight,Vertex& to);

    /**
     * @brief fix the heap
    */
    void FixHeap(Dist& dist,Heap& heap);

    /**
     * @brief check if vertex u need a fix because 
     * of vertex v
    */
    bool is_need_fix(Dist& u,Dist*& v,const Edge& edge,
    const CompWeight& compweight,Vertex &to);
    vector<Vertex> vertexs;

};