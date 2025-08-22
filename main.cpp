#include <iostream>
#include <deque>
#include <cassert>
#include "Graph.h"

using namespace std;

// פונקציה להדפסת כל הקשתות של צומת
void PrintEdges(const Vertex& v) {
    cout << "Vertex " << v.idx << " edges: ";
    for (const auto& e : v.edges) {
        cout << e.vertex->idx << "(" << e.road.dist << ") ";
    }
    cout << endl;
}

// פונקציה עזר להשוואת edges לפי idx (למיון)
bool EdgeShouldComeBefore(const Edge& newEdge, const Edge& existingEdge) {
    return newEdge.vertex->idx < existingEdge.vertex->idx;
}

// הוספת קשת בצורה ממוינת
void AddEdgeSorted(Vertex& from, Vertex& to) {
    // אם הקשת קיימת, מחזירים
    Graph* graph = from.my_graph;
    graph->AddEdge(from,to,0);
}

int main() {
    Graph graph;

    // הוספת צמתים
    size_t idx1 = graph.AddVertex(0,0);
    size_t idx2 = graph.AddVertex(1,1);
    size_t idx3 = graph.AddVertex(2,2);

    assert(idx2 > idx1);
    assert(idx3 > idx2);

    // הוספת קשתות
    AddEdgeSorted(graph[idx1], graph[idx2]);
    AddEdgeSorted(graph[idx1], graph[idx3]);
    AddEdgeSorted(graph[idx2], graph[idx3]);

    // הדפסת רשימות הקשתות
    PrintEdges(graph[idx1]); // צריך לראות idx2 ואז idx3
    PrintEdges(graph[idx2]); // צריך לראות idx3
    PrintEdges(graph[idx3]); // צריך להיות ריק

    // בדיקות assert
    assert(graph[idx1].edges.size() == 2);
    assert(graph[idx1].edges[0].vertex->idx == idx2);
    assert(graph[idx1].edges[1].vertex->idx == idx3);

    cout << "All tests passed!" << endl;
    return 0;
}
