#include "DirectedDFS.h"

void DirectedDFS::dfs(const Digraph& G, int v) {
    marked_[v] = true;
    for (int w : G.adj(v)) {
        if (!marked_[w]) dfs(G, w);
    }
}

DirectedDFS::DirectedDFS(const Digraph& G, const std::list<int>& sources) : marked_(G.V()) {
    for (int s : sources) {
        if (!marked_[s]) dfs(G, s);
    }
}
