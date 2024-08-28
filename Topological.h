#ifndef ALGS4_TOPOLOGICAL_H
#define ALGS4_TOPOLOGICAL_H


#include <deque>
#include "Digraph.h"

class Topological {
private:
    std::deque<int> order;      // 顶点的拓扑顺序

public:
    Topological(const Digraph &G);

    std::deque<int> getOrder() const { return order; }

    bool isDAG() const { return !order.empty(); }
};


#endif //ALGS4_TOPOLOGICAL_H
