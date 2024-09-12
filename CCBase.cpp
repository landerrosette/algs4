#include "CCBase.h"

void CCBase::dfs(const GraphBase<int> &G, int v) {
    marked[v] = true;
    id[v] = count;
    for (int w: G.getAdj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}
