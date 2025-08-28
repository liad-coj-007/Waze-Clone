#include "Box.h"
#include <algorithm>
#include <cmath>

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

double Box::getDistance(const double& lat,const double& lon)const{
    double dx = 0;
    if(lon < low_lon){
        dx = low_lon - lon;
    }else if(lon >= high_lon){
        dx = lon - high_lon;
    }

    double dy = 0;
    if(lat < low_lat){
        dx = low_lat - lat;
    }else if(lon >= high_lat){
        dx = lon - high_lat;
    }
    return std::sqrt(dx*dx + dy*dy);


}
