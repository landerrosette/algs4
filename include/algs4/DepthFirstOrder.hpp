#ifndef ALGS4_DEPTHFIRSTORDER_HPP
#define ALGS4_DEPTHFIRSTORDER_HPP

#include <concepts>
#include <ranges>
#include <type_traits>
#include <vector>

#include "DirectedEdge.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class DepthFirstOrder {
    private:
        std::vector<bool> marked_;
        std::vector<int> pre_, post_;

        template<typename EdgeType>
        constexpr void dfs(const GraphBase<EdgeType> &G, int v);

    public:
        template<typename EdgeType>
        constexpr explicit DepthFirstOrder(const GraphBase<EdgeType> &G);

        constexpr auto pre() const & { return std::views::all(pre_); }
        constexpr auto post() const & { return std::views::all(post_); }
        constexpr auto reversePost() const & { return std::views::reverse(post_); }
    };
}

template<typename EdgeType>
constexpr void algs4::DepthFirstOrder::dfs(const GraphBase<EdgeType> &G, int v) {
    pre_.push_back(v);
    marked_[v] = true;
    for (const auto &e: G.adj(v)) {
        int w;
        if constexpr (std::same_as<std::remove_cvref_t<decltype(e)>, DirectedEdge>) w = e.to();
        else w = e;
        if (!marked_[w])
            dfs(G, w);
    }
    post_.push_back(v);
}

template<typename EdgeType>
constexpr algs4::DepthFirstOrder::DepthFirstOrder(const GraphBase<EdgeType> &G) : marked_(G.V()) {
    for (int v = 0; v < G.V(); ++v)
        if (!marked_[v])
            dfs(G, v);
}

#endif // ALGS4_DEPTHFIRSTORDER_HPP
