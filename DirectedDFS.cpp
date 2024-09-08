#include "DirectedDFS.h"

void DirectedDFS::dfs(const Digraph &G, int v) {
    marked[v] = true;
    for (int w: G.getAdj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}

DirectedDFS::DirectedDFS(const Digraph &G, const std::forward_list<int> &sources) : marked(G.getV()) {
    for (int s: sources) {
        if (!marked[s]) dfs(G, s);
    }
}
