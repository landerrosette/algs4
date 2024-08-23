#include "DirectedDFS.h"

void DirectedDFS::dfs(const Digraph &G, int v) {
    marked[v] = true;
    for (int w: G.getAdj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}
