#ifndef ALGS4_CC_HPP
#define ALGS4_CC_HPP


#include "CCBase.hpp"
#include "Graph.hpp"

namespace algs4 {
    class CC : public CCBase {
    public:
        constexpr explicit CC(const Graph &G);
    };
}

constexpr algs4::CC::CC(const Graph &G) : CCBase(G) {
    for (int s = 0; s < G.V(); ++s) {
        if (!marked_[s]) {
            dfs(G, s);
            ++count_;
        }
    }
}


#endif //ALGS4_CC_HPP
