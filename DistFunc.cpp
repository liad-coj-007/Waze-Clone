#include "DistFunc.h"

const size_t MAX_ENTRY = 65536;

DistFunction::DistFunction(const size_t& size){
    this->size = size;
    this->map = (Dist*) mmap(nullptr, size * sizeof(Dist),
                             PROT_READ | PROT_WRITE,
                             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (this->map == MAP_FAILED) {
        throw std::runtime_error("mmap failed in DistFunction constructor");
    }
}



Dist& DistFunction::operator[]( Vertex& vertex){
    Dist& dist = map[vertex.idx];
    if(dist.vertex == nullptr){
        dist = Dist(&vertex);
    }
    return dist;
}



DistFunction::~DistFunction(){
    munmap(map,size*sizeof(Dist));
}