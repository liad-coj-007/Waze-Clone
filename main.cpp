using namespace std;
#include "Graph.h"
#include <iostream>      // for std::cout
#include <assert.h>
int main(){
    Graph graph;
    size_t idx1 = graph.AddVertex(0,0);
    size_t idx2 = graph.AddVertex(1,1);
    assert(idx2 > idx1);
    cout << graph[idx1].lon << endl;
    cout << graph[idx2].idx << endl;
    cout << graph[3].idx << endl;

    return 0;
}