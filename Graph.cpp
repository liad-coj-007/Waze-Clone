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
    for(auto it : v1.out_edges){
        if(it.vertex == &v2){
            return &it;
        }
    }
    return nullptr;
}

Edge* Graph::find_edge(const Vertex& vertex, deque<Edge>& edges){
    for(auto it : edges){
        if(it.vertex == &vertex){
            return &it;
        }
    }
    return nullptr;
}


void Graph::AddEdge( Vertex& v1, Vertex &v2,const size_t flags){
   Edge* my_edge = find_edge(v1,v2);
   if (my_edge != nullptr){
        my_edge->road.flags = flags;
        Edge* e2 = find_edge(v1,v2.in_edges);
        e2->road.flags = flags;
        return;
   }

   Edge e1(v1,v2,flags);
   v1.out_edges = std::move(AddEdge(v1.out_edges,e1));
   Edge e2(v2,v1,flags);
   v2.in_edges = std::move(AddEdge(v2.in_edges,e2));

}

deque<Edge> Graph::AddEdge(deque<Edge>& old_edges,Edge edge){
   deque<Edge> edges;
   bool is_put = false;
   for(auto it : old_edges){
       if(!is_put && *(edge.vertex) < *(it.vertex)){
            is_put = true;
            edges.push_back(edge);
       }
       edges.push_back(it);
   }

   if(!is_put){
        edges.push_back(edge);
   }

   return edges;
}






DistFunction Graph::AStar(Vertex &from, Vertex& to){
    DistFunction distfunc;
    return distfunc;
}



