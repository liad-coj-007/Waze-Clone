#include "Box.h"
#include <algorithm>

Box::Box(const double& low_lat,
         const double& low_lon,
         const double& high_lat,
         const double& high_lon)
    : low_lat(low_lat),
      low_lon(low_lon),
      high_lat(high_lat),
      high_lon(high_lon) {}

bool Box::isInBox(const double& lat,const double lon)const{
    return lat >= low_lat && lat <= high_lat 
    && lon >= low_lon && lon <= high_lon;
}


double Box::getArea()const{
    double dx = high_lat - low_lat;
    double dy = high_lon - low_lon;
    return dx*dy;
}

void Box::Union(const Box& other){
    low_lat = std::min(low_lat,other.low_lat);
    low_lon = std::min(low_lon,other.low_lon);
    high_lat = std::max(high_lat,other.high_lat);
    high_lon = std::max(high_lon,other.high_lon);
}