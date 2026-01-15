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
        std::vector<bool> marked;
        std::vector<EdgeType> edgeTo;
        std::vector<EdgeType> cycle_;
        std::vector<bool> onStack; // vertices on recursive call stack

        constexpr void dfs(const GraphBase<EdgeType> &G, int v);

    public:
        constexpr explicit DirectedCycle(const GraphBase<EdgeType> &G);

        constexpr bool hasCycle() const { return !cycle_.empty(); }
        constexpr auto cycle() const & { return std::views::reverse(cycle_); }
    };
}

template<typename EdgeType>
constexpr void algs4::DirectedCycle<EdgeType>::dfs(const GraphBase<EdgeType> &G, int v) {
    onStack[v] = true;
    marked[v] = true;
    for (const auto &e: G.adj(v)) {
        int w;
        if constexpr (std::same_as<std::remove_cvref_t<decltype(e)>, DirectedEdge>) w = e.to();
        else w = e;
        if (hasCycle()) return;
        else if (!marked[w]) {
            edgeTo[w] = e;
            dfs(G, w);
        } else if (onStack[w]) {
            if constexpr (std::same_as<std::remove_cvref_t<decltype(e)>, DirectedEdge>) {
                auto x = e;
                for (; x.from() != w; x = edgeTo[x.from()])
                    cycle_.push_back(x);
                cycle_.push_back(x);
            } else {
                for (int x = v; x != w; x = edgeTo[x])
                    cycle_.push_back(x);
                cycle_.push_back(w);
                cycle_.push_back(v);
            }
        }
    }
    onStack[v] = false;
}

template<typename EdgeType>
constexpr algs4::DirectedCycle<EdgeType>::DirectedCycle(const GraphBase<EdgeType> &G)
    : marked(G.V()), edgeTo(G.V()), onStack(G.V()) {
    for (int v = 0; v < G.V(); ++v)
        if (!marked[v])
            dfs(G, v);
}


#endif //ALGS4_DIRECTEDCYCLE_HPP
