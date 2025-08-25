#include "Graph.h"
#include "Vertex.h"
#include "CompByDist.h"
#include "DistFunc.h"
#include <iostream>
#include <chrono>

int main() {
    Graph g;

    const size_t ROWS = 1500;   // גודל גריד
    const size_t COLS = 1500;
    const size_t N = ROWS * COLS;

    CompDist comp;

    // יצירת צמתים
    std::vector<size_t> indices(N);
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            size_t idx = g.AddVertex(i, j);
            indices[i * COLS + j] = idx;
        }
    }

    // יצירת קשתות (לימין ולמטה)
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            size_t idx = i * COLS + j;
            if (j + 1 < COLS)
                g.AddEdge(g[indices[idx]], g[indices[idx + 1]], 1);
            if (i + 1 < ROWS)
                g.AddEdge(g[indices[idx]], g[indices[idx + COLS]], 1);
        }
    }

    size_t start_idx = indices[0];        // פינה עליונה שמאלית
    size_t end_idx   = indices[N - 1];    // פינה תחתונה ימנית

    auto t1 = std::chrono::high_resolution_clock::now();
    Path path = g.find_route(g[start_idx], g[end_idx], comp);
    auto t2 = std::chrono::high_resolution_clock::now();

    if (path.is_inf()) {
        std::cout << "No path found.\n";
    } else {
        std::cout << "Path size: " << path.size() << " edges\n";
    }

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "find_route elapsed time: " << elapsed_ms << " ms\n";
    std::cout << "find_route elapsed time: " << elapsed_us << " µs\n";

    return 0;
}
