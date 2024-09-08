#include "DepthFirstOrder.h"

void DepthFirstOrder::dfs(const Digraph &G, int v) {
    pre.push_back(v);
    marked[v] = true;
    for (int w: G.getAdj(v)) {
        if (!marked[w]) dfs(G, w);
    }
    post.push_back(v);
    reversePost.push_front(v);
}

DepthFirstOrder::DepthFirstOrder(const Digraph &G) : marked(G.getV()) {
    for (int v = 0; v < G.getV(); ++v) {
        if (!marked[v]) dfs(G, v);
    }
}
