#include "DirectedCycle.h"

void DirectedCycle::dfs(const Digraph &G, int v) {
    onStack[v] = true;
    marked[v] = true;
    for (int w: G.adj(v)) {
        if (hasCycle()) {
            return;
        } else if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        } else if (onStack[w]) {
            for (int x = v; x != w; x = edgeTo[x]) cycle_.push_front(x);
            cycle_.push_front(w);
            cycle_.push_front(v);
        }
    }
    onStack[v] = false;
}

DirectedCycle::DirectedCycle(const Digraph &G) : marked(G.V()), edgeTo(G.V()), onStack(G.V()) {
    for (int v = 0; v < G.V(); ++v) {
        if (!marked[v]) dfs(G, v);
    }
}
