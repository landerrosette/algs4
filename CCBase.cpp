#include "CCBase.h"

void CCBase::dfs(const GraphBase<int> &G, int v) {
    marked[v] = true;
    id_[v] = count_;
    for (int w: G.adj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}
