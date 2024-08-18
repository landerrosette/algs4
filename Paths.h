#ifndef ALGS4_PATHS_H
#define ALGS4_PATHS_H


#include "Graph.h"
#include <forward_list>

class Paths {
protected:
    bool *marked;   // 这个顶点上调用过dfs()了吗？
    int *edgeTo;    // 从起点到一个顶点的已知路径上的最后一个顶点
    const int s;    // 起点

public:
    Paths(const Graph &G, int s) : marked(new bool[G.getV()]), edgeTo(new int[G.getV()]), s(s) {}

    bool hasPathTo(int v) const { return marked[v]; }

    std::forward_list<int> pathTo(int v) const;

    virtual ~Paths() {
        delete[] marked;
        delete[] edgeTo;
    }
};


#endif //ALGS4_PATHS_H
