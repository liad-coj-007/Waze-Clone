#include "Utilities.h"
#include <cmath>

using namespace std;
void CheckRange(const size_t idx,const size_t size){
    if(idx > size){
        std::string msg = "Index " + std::to_string(idx) + 
                          " is out of range for array of size " + std::to_string(size);
        throw out_of_range(msg);
    }
}

double getDistance(const Vertex& v1,const Vertex &v2){
    double dx = v1.lat - v2.lat;
    double dy = v1.lon - v2.lon;
    return std::sqrt(dx*dx + dy*dy);
}
