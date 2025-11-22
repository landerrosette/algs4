#include "DirectedDFS.h"

void algs4::DirectedDFS::dfs(const Digraph &G, int v) {
    marked_[v] = true;
    for (int w: G.adj(v))
        if (!marked_[w])
            dfs(G, w);
}

algs4::DirectedDFS::DirectedDFS(const Digraph &G, const std::list<int> &sources) : marked_(G.V()) {
    for (int s: sources)
        if (!marked_[s])
            dfs(G, s);
}
