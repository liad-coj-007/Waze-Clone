#pragma once
#include "Dist.h"
#include <vector>
using namespace std;

class Heap{
public:
    /**
     * @brief init the heap
    */
    Heap() = default;


    /**
     * @brief push a dist to the heap
    */
    void Push(Dist& dist);

    /**
     * @brief pop the value
    */
    Dist* Pop();

    /**
     * @brief check if the heap 
     * empty
    */
    bool empty()const;

    /**
     * @brief siftup the idx
    */
    void SiftUP(const size_t idx);

    /**
     * @brief doing sift down for the idx
    */
    void SiftDown(const size_t idx);


private:
    /**
     * @brief return the min between two dist on
     * the heap
    */
    Dist*& Min(const size_t idx1,const size_t idx2);
    /**
     * @brief swap 2 dist
    */
    void Swap(Dist*& d1,Dist*& d2);
    std::vector<Dist*> heap;
  
};