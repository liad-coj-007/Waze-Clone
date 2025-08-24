#pragma once
class Vertex;   // forward declaration
class CompWeight;
#include <cstddef>  

class Road {
    // TODO: add weight logic
public:
    static constexpr size_t HIGHWAY          = 1 << 0;  // main road
    static constexpr size_t TOLL            = 1 << 1;  // payment road
    static constexpr size_t UNPAVED         = 1 << 2;  // unpaved road
    static constexpr size_t TRAFFIC_JAM     = 1 << 3;  // traffic jam
    static constexpr size_t ACCIDENT        = 1 << 4;  // has a accident
    static constexpr size_t CONSTRUCTION    = 1 << 5;  // has a constractions
    static constexpr size_t CLOSED          = 1 << 6;  // close road
    static constexpr size_t BRIDGE          = 1 << 7;  // bridge
    static constexpr size_t TUNNEL          = 1 << 8;  // tunnal
    static constexpr size_t NIGHT_LIT       = 1 << 9; // the road lighten
    /**
     * @brief build the weight road
     * @param flags - the flags of the road
     * @param v1 the vertex we out from
     * @param v2 - the vertex we sign in to
    */
    Road(const size_t flags,const Vertex& v1,const Vertex& v2);

    /**
     * @brief compute the weight base on the prioty
     * of the customer
     * @param comp - the algo compute the weight base on 
     * customer needs.
    */
    double comp_Weight(const CompWeight& comp)const;

    size_t flags;
    double dist;

};