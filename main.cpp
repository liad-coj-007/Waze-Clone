#include "Graph.h"
#include "Vertex.h"
#include "CompByDist.h"
#include <iostream>
#include <chrono>

int main() {
    Graph g;

    // פרמטרים
    const size_t ROWS = 750;    // יוצרת גריד 500x500 => 250,000 צמתים
    const size_t COLS = 750;
    const size_t N = ROWS * COLS;

    // comparator לפי מרחק
    CompDist comp;

    // יוצרים צמתים במבנה grid
    std::vector<size_t> indices(N);
    for(size_t i = 0; i < ROWS; ++i) {
        for(size_t j = 0; j < COLS; ++j) {
            size_t idx = g.AddVertex(i, j);  // צומת ב-grid
            indices[i * COLS + j] = idx;
        }
    }

    // יוצרים קשתות ל־grid
    for(size_t i = 0; i < ROWS; ++i) {
        for(size_t j = 0; j < COLS; ++j) {
            size_t idx = i * COLS + j;
            // חיבור לימין
            if(j + 1 < COLS)
                g.AddEdge(g[indices[idx]], g[indices[idx + 1]], 1);
            // חיבור למטה
            if(i + 1 < ROWS)
                g.AddEdge(g[indices[idx]], g[indices[idx + COLS]], 1);
        }
    }

    // בחירת צמתים אקראיים להתחלה וסיום (seed קבוע)
    size_t start = indices[0];              // פינה עליונה שמאלית
    size_t end   = indices[N - 1];          // פינה תחתונה ימנית

    auto t1 = std::chrono::high_resolution_clock::now();
    DistFunction distfunc = g.AStar(g[start], g[end], comp);
    auto t2 = std::chrono::high_resolution_clock::now();

    Dist& dist = distfunc[g[end]];

    if(dist.is_inf)
        std::cout << "Dist = infty\n";
    else
        std::cout << "Dist = " << dist.totaldist << "\n";

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "A* elapsed time: " << elapsed_ms << " ms\n";
    std::cout << "A* elapsed time: " << elapsed_us << " µs\n";

    return 0;
}
