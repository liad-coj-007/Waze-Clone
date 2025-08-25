#pragma once
#include <stdexcept>
#include "Vertex.h"
class Vertex;
/**
 * @brief check the idx is in the range of size
 * if don't we throw error
 * @param idx - the index
 * @param size - the size of the array
*/
void CheckRange(const size_t idx,const size_t size);

/**
 * @brief compute the distance of 2 vertexs
*/
double getDistance(const Vertex& v1,const Vertex &v2);






