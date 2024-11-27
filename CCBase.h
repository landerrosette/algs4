#ifndef ALGS4_CCBASE_H
#define ALGS4_CCBASE_H


#include "GraphBase.h"
#include <vector>

class CCBase {
protected:
    std::vector<bool> marked;
    std::vector<int> id_;
    int count_ = 0;

    void dfs(const GraphBase<int> &G, int v);

public:
    explicit CCBase(const GraphBase<int> &G) : marked(G.V()), id_(G.V()) {}

    virtual ~CCBase() = default;

    bool connected(int v, int w) const { return id_[v] == id_[w]; }

    int id(int v) const { return id_[v]; }

    int count() const { return count_; }
};


#endif //ALGS4_CCBASE_H
