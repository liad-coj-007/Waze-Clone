#include "Road.h"
#include "Vertex.h"   
#include <cmath>

Road::Road(const size_t flags,const Vertex& v1,const Vertex& v2){
    this->flags = flags;
    double dx = v1.lat - v2.lat;
    double dy = v1.lon - v2.lon;
    dist = std::sqrt(dx*dx + dy*dy);
}

double Road::comp_Weight(const CompWeight& comp)const{
    return comp.computeWeight(*this);
}