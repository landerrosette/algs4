#ifndef ALGS4_TOPOLOGICAL_H
#define ALGS4_TOPOLOGICAL_H


#include <list>
#include "GraphBase.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"

class Topological {
private:
    std::list<int> order_; // 顶点的拓扑顺序

public:
    template<typename T>
    Topological(const GraphBase<T> &G);

    std::list<int> order() const { return order_; }

    bool isDAG() const { return !order_.empty(); }
};

template<typename T>
Topological::Topological(const GraphBase<T> &G) {
    DirectedCycle cyclefinder(G);
    if (!cyclefinder.hasCycle()) {
        DepthFirstOrder dfs(G);
        order_ = dfs.reversePost();
    }
}


#endif //ALGS4_TOPOLOGICAL_H
