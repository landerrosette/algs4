#ifndef ALGS4_DIRECTEDDFS_H
#define ALGS4_DIRECTEDDFS_H


#include "Digraph.h"
#include <forward_list>
#include <vector>

class DirectedDFS {
private:
    std::vector<bool> marked;

    void dfs(const Digraph &G, int v);

public:
    DirectedDFS(const Digraph &G, int s) : marked(G.getV()) { dfs(G, s); }

    DirectedDFS(const Digraph &G, const std::forward_list<int> &sources);

    bool isMarked(int v) const { return marked[v]; }
};


#endif //ALGS4_DIRECTEDDFS_H
