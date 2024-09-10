#include "testGraph.h"
#include <Topological.h>

void testSort(const SymbolDigraph &sg) {
    Topological top(sg.getG());
    for (int v: top.getOrder()) {
        std::cout << sg.name(v) << "\n";
    }
}
