#include "Dist.h"
#include <cstddef>  
#include <functional>
#include "Vertex.h"
#include "Utilities.h"



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
    huristic = 0;
    
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

void Dist::Init(){
    is_inf = false;
    totaldist = 0;
}

Dist Dist::BuildFixDist(Dist& other,const Edge& edge,
Vertex& to,const CompWeight& compweight){
    Dist new_dist = other;
    if(new_dist.is_inf){
        return new_dist;
    }
    new_dist.vertex = edge.vertex;
    new_dist.huristic = getDistance(*(new_dist.vertex),to);
    new_dist.totaldist += edge.getWeight(compweight);
    return new_dist;
}



Dist& DistFunction::operator[]( Vertex& vertex){
    auto it = map.find(vertex);
    if(it != map.end()){
        return it->second;
    }

    map.emplace(vertex, Dist(&vertex));
    return map[vertex];
}

bool operator<(const Dist &d1,const Dist &d2){
    if(d2.is_inf && !d1.is_inf){
        return true;
    }
    return !d1.is_inf && 
    d1.totaldist + d1.huristic < d2.totaldist + d2.huristic;
}







