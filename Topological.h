#ifndef ALGS4_TOPOLOGICAL_H
#define ALGS4_TOPOLOGICAL_H


#include <list>
#include "Digraph.h"

class Topological {
private:
    std::list<int> order_; // 顶点的拓扑顺序

public:
    Topological(const Digraph& G);

    std::list<int> order() const { return order_; }

    bool isDAG() const { return !order_.empty(); }
};


#endif //ALGS4_TOPOLOGICAL_H
