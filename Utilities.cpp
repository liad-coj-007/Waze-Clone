#include "Utilities.h"

using namespace std;
void CheckRange(const size_t idx,const size_t size){
    if(idx > size){
        std::string msg = "Index " + std::to_string(idx) + 
                          " is out of range for array of size " + std::to_string(size);
        throw out_of_range(msg);
    }
} 