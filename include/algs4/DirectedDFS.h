#ifndef ALGS4_DIRECTEDDFS_H
#define ALGS4_DIRECTEDDFS_H


#include <cassert>
#include <list>
#include <vector>

#include "Digraph.h"

namespace algs4 {
    class DirectedDFS {
    private:
        std::vector<bool> marked_;
        void dfs(const Digraph &G, int v);

    public:
        DirectedDFS(const Digraph &G, int s);
        DirectedDFS(const Digraph &G, const std::list<int> &sources);

        bool marked(int v) const { return marked_[v]; }
    };
}

inline void algs4::DirectedDFS::dfs(const Digraph &G, int v) {
    marked_[v] = true;
    for (int w: G.adj(v))
        if (!marked_[w])
            dfs(G, w);
}

inline algs4::DirectedDFS::DirectedDFS(const Digraph &G, int s) : marked_(G.V()) {
    assert(s >= 0 && s < marked_.size());
    dfs(G, s);
}

inline algs4::DirectedDFS::DirectedDFS(const Digraph &G, const std::list<int> &sources) : marked_(G.V()) {
    assert(!sources.empty());
    for (int s: sources) {
        assert(s >= 0 && s < marked_.size());
        if (!marked_[s])
            dfs(G, s);
    }
}


#endif //ALGS4_DIRECTEDDFS_H
