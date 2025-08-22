#include "Graph.h"
#include "Utilities.h"
size_t Graph::AddVertex(const double& lat,const double &lon){
    Vertex vert(lat,lon);
    vertexs.push_back(vert);
    size_t idx =  vertexs.size() - 1;
    vertexs[idx].idx = idx;
    return idx;
}

Vertex& Graph::operator[](const size_t idx){
    CheckRange(idx,vertexs.size());
    return vertexs[idx];
}