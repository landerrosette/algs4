#ifndef ALGS4_KOSARAJUSCC_H
#define ALGS4_KOSARAJUSCC_H


#include "CCBase.h"
#include "DepthFirstOrder.h"
#include "Digraph.h"

namespace algs4 {
    class KosarajuSCC : public CCBase {
    public:
        explicit KosarajuSCC(const Digraph &G);

        bool stronglyConnected(int v, int w) const { return connected(v, w); }
    };
}

inline algs4::KosarajuSCC::KosarajuSCC(const Digraph &G) : CCBase(G) {
    DepthFirstOrder order(G.reverse());
    for (int s: order.reversePost()) {
        if (!marked[s]) {
            dfs(G, s);
            ++count_;
        }
    }
}


#endif //ALGS4_KOSARAJUSCC_H
