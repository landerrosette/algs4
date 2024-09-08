#ifndef ALGS4_DIRECTEDCYCLE_H
#define ALGS4_DIRECTEDCYCLE_H


#include <deque>
#include "Digraph.h"
#include <vector>

class DirectedCycle {
private:
    std::vector<bool> marked;
    std::vector<int> edgeTo;
    std::deque<int> cycle;
    std::vector<bool> onStack;           // 栈上的所有顶点

    void dfs(const Digraph &G, int v);

public:
    DirectedCycle(const Digraph &G);

    bool hasCycle() const { return !cycle.empty(); }

    std::deque<int> getCycle() const { return cycle; }
};


#endif //ALGS4_DIRECTEDCYCLE_H
