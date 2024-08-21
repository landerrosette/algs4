#include "testGraph.h"
#include <iostream>
#include <forward_list>

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

void testCC(const Graph &G, CC &&cc) {
    int M = cc.getCount();
    std::cout << M << " components" << "\n";

    std::forward_list<int> components[M];
    for (int v = 0; v < G.getV(); ++v) components[cc.getId(v)].push_front(v);
    for (int i = 0; i < M; ++i) {
        for (int v: components[i]) std::cout << v << " ";
        std::cout << "\n";
    }
}
