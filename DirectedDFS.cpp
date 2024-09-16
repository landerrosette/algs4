#include "DirectedDFS.h"

void DirectedDFS::dfs(const Digraph& G, int v) {
    marked_[v] = true;
    for (int w : G.adj(v)) {
        if (!marked_[w]) dfs(G, w);
    }
}
