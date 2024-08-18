#include "testPaths.h"
#include <iostream>

void testPaths(const Graph &G, Paths &&search, int s) {
    for (int v = 0; v < G.getV(); ++v) {
        std::cout << s << " to " << v << ": ";
        if (search.hasPathTo(v)) {
            for (int x: search.pathTo(v)) {
                if (x == s) std::cout << x;
                else std::cout << "-" << x;
            }
        }
        std::cout << "\n";
    }
}
