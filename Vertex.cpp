#include "Vertex.h"
#include <cmath>
#include "Road.h"

Vertex::Vertex(const double &lat,const double& lon){
    this->lat = lat;
    this->lon = lon;
}



Edge::Edge(Vertex &v1,Vertex &v2,const size_t flags):road(flags,v1,v2){
    this->vertex = &v2;
}

double Edge::getWeight(const CompWeight& compweight)const{
    return road.comp_Weight(compweight);
}


bool operator<(const Vertex& v1,const Vertex &v2){
    if(v1.lat < v2.lat){
        return true;
    }
    return v1.lat == v2.lat && v1.lon < v2.lon;
}

bool operator==(const Vertex& v1,const Vertex& v2){
    return v1.lat == v2.lat && v1.lon == v2.lon;
}

