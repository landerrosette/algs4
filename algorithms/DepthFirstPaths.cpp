#include "DepthFirstPaths.h"

void algs4::DepthFirstPaths::dfs(const Graph &G, int v) {
    marked[v] = true;
    for (int w: G.adj(v)) {
        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}