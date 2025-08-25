#include "Graph.h"
#include "Utilities.h"

Path::Path(DistFunction& distfunc,Vertex& vertex){
    dist = distfunc[vertex];
}


bool Path::is_inf()const{
    return dist.is_inf;
}

size_t Path::size()const{
    return edges.size();
}

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

Edge* Graph::find_edge( Vertex& v1, Vertex& v2)const{
    int idx = find_edge(v1.out_edges,v2);
    if(!v1.out_edges.empty() && *(v1.out_edges[idx].vertex) == v2){
        return &(v1.out_edges[idx]);
    }
    return nullptr;
}

int Graph::find_edge(const vector<Edge>& edges,const Vertex& v2)const{
    int right = edges.size() - 1;
    int left = 0;
    int mid = 0;
    while(left <= right){
        mid = (left + right)/2;
        const Vertex v = *(edges[mid].vertex);
        if(v == v2){
            return mid;
        }
        if(v < v2){
            left = mid +1;
        }else{
            right = mid - 1;
        }
    }
    return mid;
}


Edge* Graph::find_edge(const Vertex& vertex, vector<Edge>& edges){
    int idx = find_edge(edges,vertex);
    if(!edges.empty() && *(edges[idx].vertex) == vertex){
        return &(edges[idx]);
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
   AddEdge(v1.out_edges,e1);
   Edge e2(v2,v1,flags);
   AddEdge(v2.in_edges,e2);
}

void Graph::AddEdge(vector<Edge>& old_edges,Edge edge){
    old_edges.push_back(edge);
    int swap_idx = old_edges.size() -1;
    int idx = find_edge(old_edges,*(edge.vertex));
    for(int i = idx; i < swap_idx; i++){
        if(*(old_edges[i].vertex) < *(old_edges[swap_idx].vertex)){
            std::swap(old_edges[i],old_edges[swap_idx]);
        }
    }

}




void Graph::InitAStar(Heap& heap,Vertex &from,DistFunction& distfunc){
    Dist& dist = distfunc[from];
    dist.Init();
    heap.Push(dist);
}

void Graph::FixHeap(Dist& dist,Heap& heap){
    if(dist.is_on_heap){
        heap.SiftUP(dist.heap_idx);
        return;
    }
    heap.Push(dist);
}



void Graph::FixDist(Dist*& dist,Heap& heap,DistFunction& distfunc,
const CompWeight& compweight,Vertex &to){
    Vertex* vert = dist->vertex;
    for(auto& edge: vert->out_edges){
        Dist& edge_dist = distfunc[*(edge.vertex)];
        if(is_need_fix(edge_dist,dist,edge,compweight,to)){
            FixHeap(edge_dist,heap);
        }
    }
}

bool Graph::is_need_fix(Dist& u,Dist*& v,
const Edge& edge,const CompWeight& compweight,Vertex& to){
    Dist new_dist = u.BuildFixDist(*v,edge,to,compweight);
    bool is_fixed = new_dist < u;
    if(is_fixed){
        u = new_dist;
    }
    return is_fixed;
}

Path Graph::find_route( Vertex& from, Vertex &dest,const CompWeight& comp){
    DistFunction distfunc = AStar(from,dest,comp);
    Path path(distfunc,dest);
    Vertex& current = dest;
    if(path.is_inf()){
        return path;
    }

    while(!(current == from)){
        Edge& tmp = find_next_vertex(current,distfunc,comp);
        path.edges.push_front(tmp);
        current = *(tmp.vertex);
    }
    return path;
}

Edge& Graph::find_next_vertex(Vertex &v,DistFunction& distfunc,
    const CompWeight& compweight){
        double v_dist = distfunc[v].totaldist;
        for(auto& it : v.in_edges){
            double edge_dist =  distfunc[*(it.vertex)].totaldist + it.getWeight(compweight);
            if(v_dist == edge_dist){
                return it;
            }
        }
        //not happend
        throw std::runtime_error("error!");
}


DistFunction Graph::AStar(Vertex &from, Vertex& to,const CompWeight& compweight){
    DistFunction distfunc(vertexs.size());
    Heap heap;
    InitAStar(heap,from,distfunc);
    while(!heap.empty()){
        Dist* dist = heap.Pop();
        if(dist->vertex == &to){
            break;
        }
        FixDist(dist,heap,distfunc,compweight,to);
    }
    return distfunc;
}



