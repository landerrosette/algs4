#ifndef ALGS4_CCBASE_H
#define ALGS4_CCBASE_H


#include "GraphBase.h"
#include <vector>

class CCBase {
protected:
    std::vector<bool> marked;
    std::vector<int> id;
    int count = 0;

    void dfs(const GraphBase<int> &G, int v);

public:
    CCBase(const GraphBase<int> &G) : marked(G.getV()), id(G.getV()) {}

    virtual ~CCBase() = default;

    bool connected(int v, int w) const { return id[v] == id[w]; }

    int getId(int v) const { return id[v]; }

    int getCount() const { return count; }
};


#endif //ALGS4_CCBASE_H
