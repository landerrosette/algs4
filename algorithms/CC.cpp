#include "CC.h"

CC::CC(const Graph &G) : CCBase(G) {
    for (int s = 0; s < G.V(); ++s) {
        if (!marked[s]) {
            dfs(G, s);
            ++count_;
        }
    }
}
