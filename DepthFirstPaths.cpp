#include "DepthFirstPaths.h"

void DepthFirstPaths::dfs(const Graph& G, int v) {
    marked[v] = true;
    for (int w : G.adj(v)) {
        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}
