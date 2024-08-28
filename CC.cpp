#include "CC.h"

void CC::dfs(const Graph &G, int v) {
    marked[v] = true;
    id[v] = count;
    for (int w: G.getAdj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}

CC::CC(const Graph &G) : marked(G.getV()), id(G.getV()) {
    for (int s = 0; s < G.getV(); ++s) {
        if (!marked[s]) {
            dfs(G, s);
            ++count;
        }
    }
}
