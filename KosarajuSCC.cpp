#include "KosarajuSCC.h"

KosarajuSCC::KosarajuSCC(const Digraph &G) {
    marked = std::vector<bool>(G.getV());
    id = std::vector<int>(G.getV());
    DepthFirstOrder order(G.reverse());
    for (int s: order.getReversePost()) {
        if (!marked[s]) {
            dfs(G, s);
            ++count;
        }
    }
}
