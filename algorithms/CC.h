#ifndef ALGS4_CC_H
#define ALGS4_CC_H


#include "CCBase.h"
#include "Graph.h"

namespace algs4 {
    class CC : public CCBase {
    public:
        explicit CC(const Graph &G);
    };
}

inline algs4::CC::CC(const Graph &G) : CCBase(G) {
    for (int s = 0; s < G.V(); ++s) {
        if (!marked[s]) {
            dfs(G, s);
            ++count_;
        }
    }
}


#endif //ALGS4_CC_H
