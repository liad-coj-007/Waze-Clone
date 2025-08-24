#include "Heap.h"
#include <cassert>
#include <iostream>

void sort(Dist*& arr,const int n,const int testnum);

void TestSort( Dist* dist,const int n,const int testnum);

void Test();

Dist* GenerateRandomDistArray(int n) {
    Dist* arr = new Dist[n]();

    for(int i = 0; i < n; ++i) {
        arr[i].totaldist = rand() % (n + 1); 
        arr[i].is_inf = false;
        arr[i].heap_idx = 0;
        arr[i].is_on_heap = false;
        arr[i].vertex = nullptr; 
    }

    return arr;
}

void ErrorMsg(const int idx,const Dist& d1,const Dist& d2);


int main() {
    Test();
    return 0;
}

void ErrorMsg(const int idx,const Dist& d1,const Dist& d2){
    cout << "(" << (idx -1) << ", " << d1.totaldist << ")\t>\t";
    cout << "(" << (idx) << ", " << d2.totaldist << ")" << endl;
}

void Test(){
    int tests[] = {1,100,10000,200000,123456};
    const int n = 5;
    for(int i = 0;i < n; i++){
        Dist* arr = GenerateRandomDistArray(tests[i]);
        sort(arr,tests[i],i);
        delete [] arr;
    }
}

void sort(Dist*& arr,const int n,const int testnum){
    Heap heap;
    for(int i = 0; i < n; i++){
        heap.Push(arr[i]);
    }

    Dist* sort_arr = new Dist[n]();
    for(int i = 0; i < n; i++){
        Dist* dist = heap.Pop();
        sort_arr[i] = *dist;
    }
    TestSort(sort_arr,n,testnum);
    delete [] sort_arr;
}

void TestSort( Dist* dist,const int n,const int testnum){
    for(int i = 1; i < n; i++){
        
        bool is_correct = (dist[i-1].totaldist <= dist[i].totaldist);
        if(!is_correct){
            ErrorMsg(i,dist[i-1],dist[i]);
        }
        assert(is_correct);
    }

    std::cout << "\033[1;32m"; // Bold Green
    std::cout << "Test " << testnum << " passed!\n";
    std::cout << "\033[0m"; // Reset color
    std::cout << "=======================" << std::endl;
}