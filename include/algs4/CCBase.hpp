#ifndef ALGS4_CCBASE_H
#define ALGS4_CCBASE_H


#include <cassert>
#include <vector>

#include "GraphBase.h"

namespace algs4 {
    class CCBase {
    protected:
        std::vector<bool> marked;
        std::vector<int> id_;
        int count_ = 0;

        explicit CCBase(const GraphBase<int> &G) : marked(G.V()), id_(G.V()) {}
        ~CCBase() = default;

        void dfs(const GraphBase<int> &G, int v);

    public:
        bool connected(int v, int w) const;
        int id(int v) const;
        int count() const { return count_; }
    };
}

inline void algs4::CCBase::dfs(const GraphBase<int> &G, int v) {
    marked[v] = true;
    id_[v] = count_;
    for (int w: G.adj(v))
        if (!marked[w])
            dfs(G, w);
}

inline bool algs4::CCBase::connected(int v, int w) const {
    assert(v >= 0 && v < marked.size());
    assert(w >= 0 && w < marked.size());
    return id_[v] == id_[w];
}

inline int algs4::CCBase::id(int v) const {
    assert(v >= 0 && v < marked.size());
    return id_[v];
}


#endif //ALGS4_CCBASE_H
