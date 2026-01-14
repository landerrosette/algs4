#ifndef ALGS4_TOPOLOGICAL_HPP
#define ALGS4_TOPOLOGICAL_HPP


#include <ranges>
#include <vector>

#include "DepthFirstOrder.hpp"
#include "DirectedCycle.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class Topological {
    private:
        std::vector<int> order_; // topological order

    public:
        template<typename EdgeType>
        explicit Topological(const GraphBase<EdgeType> &G);

        auto order() const & { return std::views::all(order_); }
        bool isDAG() const { return !order_.empty(); }
    };
}

template<typename EdgeType>
algs4::Topological::Topological(const GraphBase<EdgeType> &G) {
    DirectedCycle cyclefinder(G);
    if (!cyclefinder.hasCycle()) {
        DepthFirstOrder dfs(G);
        auto reversePost = dfs.reversePost();
        order_ = {reversePost.begin(), reversePost.end()};
    }
}


#endif //ALGS4_TOPOLOGICAL_HPP
