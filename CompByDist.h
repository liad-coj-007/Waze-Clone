#pragma once
#include "CompWeight.h"
class CompDist : public CompWeight{
public:
    virtual double computeWeight(const Road &road) const override;
    ~CompDist() = default;
};