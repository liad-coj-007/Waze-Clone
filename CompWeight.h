#pragma once
#include "Utilities.h"
#include "Road.h"

class CompWeight{
public:
    /**
     * @brief compute the weight of the edge
    */
    virtual double computeWeight(const Road &road) const = 0;
    virtual ~CompWeight() = default;
};