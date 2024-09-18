#include "testGraph.h"
#include <iostream>
#include <list>

void testPaths(const Graph& G, int s, const Paths& search) {
    for (int v = 0; v < G.V(); ++v) {
        std::cout << s << " to " << v << ": ";
        if (search.hasPathTo(v)) {
            for (int x : search.pathTo(v)) {
                if (x == s) std::cout << x;
                else std::cout << "-" << x;
            }
        }
        std::cout << "\n";
    }
}

void testCC(const GraphBase<int>& G, const CCBase& cc) {
    int M = cc.count();
    std::cout << M << " components" << "\n";

    std::list<int> components[M];
    for (int v = 0; v < G.V(); ++v) components[cc.id(v)].push_front(v);
    for (int i = 0; i < M; ++i) {
        for (int v : components[i]) std::cout << v << " ";
        std::cout << "\n";
    }
}

void testSearch(const Digraph& G, const DirectedDFS& reachable) {
    for (int v = 0; v < G.V(); ++v) {
        if (reachable.marked(v)) std::cout << v << " ";
    }
    std::cout << "\n";
}

void testTopological(const SymbolDigraph& G, const Topological& top) {
    for (int v : top.order()) {
        std::cout << G.name(v) << "\n";
    }
}

void testMST(const EdgeWeightedGraph& G, const MST& mst) {
    for (const auto& e : mst.edges()) {
        std::cout << e << "\n";
    }
    std::cout << mst.weight() << "\n";
}
