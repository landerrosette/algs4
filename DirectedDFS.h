#ifndef ALGS4_DIRECTEDDFS_H
#define ALGS4_DIRECTEDDFS_H


#include "Digraph.h"
#include <vector>
#include <list>

class DirectedDFS {
private:
    std::vector<bool> marked_;

    void dfs(const Digraph &G, int v);

public:
    DirectedDFS(const Digraph &G, int s) : marked_(G.V()) { dfs(G, s); }

    DirectedDFS(const Digraph &G, const std::list<int> &sources);

    bool marked(int v) const { return marked_[v]; }
};


#endif //ALGS4_DIRECTEDDFS_H
