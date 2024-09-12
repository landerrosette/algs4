#include "KosarajuSCC.h"
#include "DepthFirstOrder.h"

KosarajuSCC::KosarajuSCC(const Digraph &G) : CCBase(G) {
    DepthFirstOrder order(G.reverse());
    for (int s: order.getReversePost()) {
        if (!marked[s]) {
            dfs(G, s);
            ++count;
        }
    }
}
