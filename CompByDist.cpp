#include "CompByDist.h"

double CompDist::computeWeight(const Road &road) const {
    return road.dist;
}