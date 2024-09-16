#ifndef ALGS4_DIRECTEDDFS_H
#define ALGS4_DIRECTEDDFS_H


#include "Digraph.h"
#include <vector>

class DirectedDFS {
private:
    std::vector<bool> marked_;

    void dfs(const Digraph &G, int v);

public:
    DirectedDFS(const Digraph &G, int s) : marked_(G.V()) { dfs(G, s); }

    template<typename Iterable>
    DirectedDFS(const Digraph &G, const Iterable &sources);

    bool marked(int v) const { return marked_[v]; }
};

template<typename Iterable>
DirectedDFS::DirectedDFS(const Digraph &G, const Iterable &sources) : marked_(G.V()) {
    for (int s: sources) {
        if (!marked_[s]) dfs(G, s);
    }
}


#endif //ALGS4_DIRECTEDDFS_H
