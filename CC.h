#ifndef ALGS4_CC_H
#define ALGS4_CC_H


#include "Graph.h"
#include <vector>

class CC {
protected:
    std::vector<bool> marked;
    std::vector<int> id;
    int count = 0;

    template<class GraphType>
    void dfs(const GraphType &G, int v);

    CC() = default;

public:
    CC(const Graph &G);

    bool connected(int v, int w) const { return id[v] == id[w]; }

    int getId(int v) const { return id[v]; }

    int getCount() const { return count; }
};

template<class GraphType>
void CC::dfs(const GraphType &G, int v) {
    marked[v] = true;
    id[v] = count;
    for (int w: G.getAdj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}

#endif //ALGS4_CC_H
