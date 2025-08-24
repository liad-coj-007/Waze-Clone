#include "Dist.h"
#include <cstddef>  
#include <functional>
#include "Vertex.h"



size_t VertexHash::operator()(const Vertex& v)const{
     std::size_t h1 = std::hash<double>{}(v.lat);
     std::size_t h2 = std::hash<double>{}(v.lon);
     return h1 ^ (h2 << 1); 
}

Dist::Dist(Vertex* vertex){
    this->vertex = vertex;
    this->totaldist = 0;
    this->is_inf = true;
    is_on_heap = false;
    heap_idx = 0;
    
}

void Dist::SetDist(const double &dist){
    this->totaldist = dist;
    this->is_inf = false;
}

bool Dist::FixDist(const double &dist){
    if(is_inf){
        SetDist(dist);
        return true;
    }

    if(dist >= this->totaldist){
        return false;
    }
    SetDist(dist);
}

Dist::Dist():Dist(nullptr){}

Dist& DistFunction::operator[]( Vertex& vertex){
    auto it = map.find(vertex);
    if(it != map.end()){
        return it->second;
    }

    map.emplace(vertex, Dist(&vertex));
    return map[vertex];
}

bool operator<(const Dist &d1,const Dist &d2){
    return !d1.is_inf && d1.totaldist < d2.totaldist;
}







