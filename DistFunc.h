#pragma once
#include "Dist.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdexcept>




class DistFunction{
public:
    DistFunction(const size_t& size);
    /**
     * @brief get the dist of vertex if it don't exist create a new one
     * and return it
     * @return the dist of the vertex
    */
    Dist& operator[]( Vertex &vertex);

    /**
     * @brief destuctor of distfunction
    */
    ~DistFunction();
private:
    Dist* map;
    size_t size;
};