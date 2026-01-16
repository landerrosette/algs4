#ifndef ALGS4_DIRECTEDCYCLE_HPP
#define ALGS4_DIRECTEDCYCLE_HPP


#include <concepts>
#include <ranges>
#include <type_traits>
#include <vector>

#include "DirectedEdge.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    template<typename EdgeType>
    class DirectedCycle {
    private:
        std::vector<bool> marked_;
        std::vector<EdgeType> edgeTo_;
        std::vector<EdgeType> cycle_;
        std::vector<bool> onStack_; // vertices on recursive call stack

        constexpr void dfs(const GraphBase<EdgeType> &G, int v);

    public:
        constexpr explicit DirectedCycle(const GraphBase<EdgeType> &G);

        constexpr bool hasCycle() const { return !cycle_.empty(); }
        constexpr auto cycle() const & { return std::views::reverse(cycle_); }
    };
}

template<typename EdgeType>
constexpr void algs4::DirectedCycle<EdgeType>::dfs(const GraphBase<EdgeType> &G, int v) {
    onStack_[v] = true;
    marked_[v] = true;
    for (const auto &e: G.adj(v)) {
        int w;
        if constexpr (std::same_as<std::remove_cvref_t<decltype(e)>, DirectedEdge>) w = e.to();
        else w = e;
        if (hasCycle()) return;
        else if (!marked_[w]) {
            edgeTo_[w] = e;
            dfs(G, w);
        } else if (onStack_[w]) {
            if constexpr (std::same_as<std::remove_cvref_t<decltype(e)>, DirectedEdge>) {
                auto x = e;
                for (; x.from() != w; x = edgeTo_[x.from()])
                    cycle_.push_back(x);
                cycle_.push_back(x);
            } else {
                for (int x = v; x != w; x = edgeTo_[x])
                    cycle_.push_back(x);
                cycle_.push_back(w);
                cycle_.push_back(v);
            }
        }
    }
    onStack_[v] = false;
}

template<typename EdgeType>
constexpr algs4::DirectedCycle<EdgeType>::DirectedCycle(const GraphBase<EdgeType> &G)
    : marked_(G.V()), edgeTo_(G.V()), onStack_(G.V()) {
    for (int v = 0; v < G.V(); ++v)
        if (!marked_[v])
            dfs(G, v);
}


#endif //ALGS4_DIRECTEDCYCLE_HPP
