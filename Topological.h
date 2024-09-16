#ifndef ALGS4_TOPOLOGICAL_H
#define ALGS4_TOPOLOGICAL_H


#include <deque>
#include "Digraph.h"

class Topological {
private:
    std::deque<int> order_; // 顶点的拓扑顺序

public:
    Topological(const Digraph& G);

    std::deque<int> order() const { return order_; }

    bool isDAG() const { return !order_.empty(); }
};


#endif //ALGS4_TOPOLOGICAL_H
