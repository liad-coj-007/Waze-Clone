#include "Heap.h"
#include "Utilities.h"
#include <algorithm>
#include <cassert>
bool Heap::empty()const{
    return heap.size() == 0;
}

void Heap::Push(Dist& dist){
    if(dist.is_on_heap){
        return;
    }
    dist.is_on_heap = true;
    heap.push_back(&dist);
    size_t idx = heap.size() - 1;
    heap[idx]->heap_idx = idx;
    SiftUP(dist.heap_idx);
}

void Heap::SiftUP(const size_t idx){
    if(idx == 0){
        return;
    }

    size_t father_idx = (idx - 1) / 2;
    Dist* d1 = heap[idx];
    if(*(heap[idx]) <  *(heap[father_idx])){
        Swap(heap[idx],heap[father_idx]);
        SiftUP(father_idx);
    }
}

void Heap::Swap(Dist*& d1,Dist*& d2){
    std::swap(d1->heap_idx, d2->heap_idx); 
    std::swap(d1, d2);  
}

Dist*& Heap::Min(const size_t idx1,const size_t idx2){
    if(idx2 >= heap.size()){
        return  heap[idx1];
    }

    if(*(heap[idx1]) < *(heap[idx2])){
        return heap[idx1];
    }
    return heap[idx2];
}


void Heap::SiftDown(const size_t idx){
    size_t left = 2*idx + 1;
    size_t right = 2*idx + 2;
    if(left >= heap.size()){
        return;
    }
    Dist*& dist = Min(left,right);
    if(*(dist) < *(heap[idx])){
        size_t child_idx = dist->heap_idx;
        Swap(dist,heap[idx]);
        SiftDown(child_idx);
    }
}


Dist* Heap::Pop(){
    if(empty()){
        return nullptr;
    }

    Dist* dist = heap[0]; 
    swap(heap[0],heap[heap.size() -1]);
    heap.pop_back();
    SiftDown(0);
    dist->is_on_heap = false;
    dist->heap_idx = 0;
    return dist;
}