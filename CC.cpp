#include "CC.h"

CC::CC(const Graph &G) : marked(G.getV()), id(G.getV()) {
    for (int s = 0; s < G.getV(); ++s) {
        if (!marked[s]) {
            dfs(G, s);
            ++count;
        }
    }
}

void CC::dfs(const GraphBase<int> &G, int v) {
    marked[v] = true;
    id[v] = count;
    for (int w: G.getAdj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}
