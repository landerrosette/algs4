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
        std::vector<bool> marked;
        std::vector<int> pre_, post_;

        template<typename EdgeType>
        void dfs(const GraphBase<EdgeType> &G, int v);

    public:
        template<typename Edge>
        explicit DepthFirstOrder(const GraphBase<Edge> &G);

        auto pre() const & { return std::views::all(pre_); }
        auto post() const & { return std::views::all(post_); }
        auto reversePost() const & { return std::views::reverse(post_); }
    };
}

template<typename EdgeType>
void algs4::DepthFirstOrder::dfs(const GraphBase<EdgeType> &G, int v) {
    pre_.push_back(v);
    marked[v] = true;
    for (const auto &e: G.adj(v)) {
        int w;
        if constexpr (std::same_as<std::remove_cvref_t<decltype(e)>, DirectedEdge>) w = e.to();
        else w = e;
        if (!marked[w])
            dfs(G, w);
    }
    post_.push_back(v);
}

template<typename EdgeType>
algs4::DepthFirstOrder::DepthFirstOrder(const GraphBase<EdgeType> &G) : marked(G.V()) {
    for (int v = 0; v < G.V(); ++v)
        if (!marked[v])
            dfs(G, v);
}


#endif //ALGS4_DEPTHFIRSTORDER_HPP
