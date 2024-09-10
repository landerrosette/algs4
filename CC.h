#ifndef ALGS4_CC_H
#define ALGS4_CC_H


#include "GraphBase.h"
#include "Graph.h"
#include <vector>

class CC {
protected:
    std::vector<bool> marked;
    std::vector<int> id;
    int count = 0;

    void dfs(const GraphBase<int> &G, int v);

    CC() = default;

public:
    CC(const Graph &G);

    bool connected(int v, int w) const { return id[v] == id[w]; }

    int getId(int v) const { return id[v]; }

    int getCount() const { return count; }
};


#endif //ALGS4_CC_H
