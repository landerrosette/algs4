#include "DirectedCycle.h"

void DirectedCycle::dfs(const Digraph &G, int v) {
    onStack[v] = true;
    marked[v] = true;
    for (int w: G.getAdj(v)) {
        if (hasCycle()) {
            return;
        } else if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        } else if (onStack[w]) {
            for (int x = v; x != w; x = edgeTo[x]) cycle.push_front(x);
            cycle.push_front(w);
            cycle.push_front(v);
        }
    }
    onStack[v] = false;
}
