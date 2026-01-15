#ifndef ALGS4_KOSARAJUSCC_HPP
#define ALGS4_KOSARAJUSCC_HPP


#include "CCBase.hpp"
#include "DepthFirstOrder.hpp"
#include "Digraph.hpp"

namespace algs4 {
    class KosarajuSCC : public CCBase {
    public:
        constexpr explicit KosarajuSCC(const Digraph &G);

        constexpr bool stronglyConnected(int v, int w) const { return connected(v, w); }
    };
}

constexpr algs4::KosarajuSCC::KosarajuSCC(const Digraph &G) : CCBase(G) {
    DepthFirstOrder order(G.reverse());
    for (int s: order.reversePost()) {
        if (!marked[s]) {
            dfs(G, s);
            ++count_;
        }
    }
}


#endif //ALGS4_KOSARAJUSCC_HPP
