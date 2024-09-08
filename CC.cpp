#include "CC.h"

CC::CC(const Graph &G) : marked(G.getV()), id(G.getV()) {
    for (int s = 0; s < G.getV(); ++s) {
        if (!marked[s]) {
            dfs(G, s);
            ++count;
        }
    }
}
