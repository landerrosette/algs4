#include "DepthFirstOrder.h"

void DepthFirstOrder::dfs(const Digraph& G, int v) {
    pre_.push_back(v);
    marked[v] = true;
    for (int w : G.adj(v)) {
        if (!marked[w]) dfs(G, w);
    }
    post_.push_back(v);
    reversePost_.push_front(v);
}

DepthFirstOrder::DepthFirstOrder(const Digraph& G) : marked(G.V()) {
    for (int v = 0; v < G.V(); ++v) {
        if (!marked[v]) dfs(G, v);
    }
}
