#include "Graph.h"
#include "Utilities.h"
size_t Graph::AddVertex(const double& lat,const double &lon){
    Vertex vert(lat,lon);
    vert.my_graph = this;
    vertexs.push_back(vert);
    size_t idx =  vertexs.size() - 1;
    vertexs[idx].idx = idx;
    return idx;
}

Vertex& Graph::operator[](const size_t idx){
    CheckRange(idx,vertexs.size());
    return vertexs[idx];
}

Edge* Graph::find_edge(const Vertex& v1,const Vertex& v2)const{
    for(auto it : v1.edges){
        if(it.vertex == &v2){
            return &it;
        }
    }
    return nullptr;
}

void Graph::AddEdge( Vertex& v1, Vertex &v2,const size_t flags){
   Edge* my_edge = find_edge(v1,v2);
   if (my_edge != nullptr){
        my_edge->road.flags = flags;
        return;
   }

   std::deque<Edge> edges;
   Edge edge(v1,v2,flags);
   bool is_put = false;
   for(auto it : v1.edges){
       if(!is_put && v2 < *(it.vertex)){
            is_put = true;
            edges.push_back(edge);
       }
       edges.push_back(it);
   }

   if(!is_put){
        edges.push_back(edge);
   }

   v1.edges = std::move(edges);
}
