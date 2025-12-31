#ifndef ALGS4_TOPOLOGICAL_HPP
#define ALGS4_TOPOLOGICAL_HPP


#include <list>

#include "DepthFirstOrder.hpp"
#include "DirectedCycle.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class Topological {
    private:
        std::list<int> order_; // topological order

    public:
        template<typename T>
        explicit Topological(const GraphBase<T> &G);

        std::list<int> order() const { return order_; }
        bool isDAG() const { return !order_.empty(); }
    };
}

template<typename T>
algs4::Topological::Topological(const GraphBase<T> &G) {
    DirectedCycle cyclefinder(G);
    if (!cyclefinder.hasCycle()) {
        DepthFirstOrder dfs(G);
        order_ = dfs.reversePost();
    }
}


#endif //ALGS4_TOPOLOGICAL_HPP
