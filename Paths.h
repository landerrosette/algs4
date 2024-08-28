#ifndef ALGS4_PATHS_H
#define ALGS4_PATHS_H


#include "Graph.h"
#include <deque>
#include <vector>

class Paths {
protected:
    std::vector<bool> marked;   // 这个顶点上调用过dfs()了吗？
    std::vector<int> edgeTo;    // 从起点到一个顶点的已知路径上的最后一个顶点
    const int s;                // 起点

public:
    Paths(const Graph &G, int s) : marked(G.getV()), edgeTo(G.getV()), s(s) {}

    bool hasPathTo(int v) const { return marked[v]; }

    std::deque<int> pathTo(int v) const;
};


#endif //ALGS4_PATHS_H
