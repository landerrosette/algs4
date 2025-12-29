#ifndef ALGS4_DIRECTEDDFS_H
#define ALGS4_DIRECTEDDFS_H


#include <list>
#include <vector>

#include "Digraph.h"

namespace algs4 {
    class DirectedDFS {
    private:
        std::vector<bool> marked_;
        void dfs(const Digraph &G, int v);

    public:
        DirectedDFS(const Digraph &G, int s) : marked_(G.V()) { dfs(G, s); }
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

inline algs4::DirectedDFS::DirectedDFS(const Digraph &G, const std::list<int> &sources) : marked_(G.V()) {
    for (int s: sources)
        if (!marked_[s])
            dfs(G, s);
}


#endif //ALGS4_DIRECTEDDFS_H
