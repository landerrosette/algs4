#ifndef ALGS4_DIRECTEDDFS_H
#define ALGS4_DIRECTEDDFS_H


#include "Digraph.h"
#include <forward_list>

class DirectedDFS {
private:
    bool *marked;

    void dfs(const Digraph &G, int v);

public:
    DirectedDFS(const Digraph &G, int s) : marked(new bool[G.getV()]) { dfs(G, s); }

    DirectedDFS(const Digraph &G, const std::forward_list<int> &sources) :
            marked(new bool[G.getV()]) { for (int s: sources) if (!marked[s]) dfs(G, s); }

    bool isMarked(int v) const { return marked[v]; }

    ~DirectedDFS() { delete[] marked; }
};


#endif //ALGS4_DIRECTEDDFS_H
