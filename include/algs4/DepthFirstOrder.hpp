#ifndef ALGS4_DEPTHFIRSTORDER_HPP
#define ALGS4_DEPTHFIRSTORDER_HPP


#include <list>
#include <type_traits>
#include <vector>

#include "DirectedEdge.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class DepthFirstOrder {
    private:
        std::vector<bool> marked;
        std::list<int> pre_, post_, reversePost_;

        template<typename T>
        void dfs(const GraphBase<T> &G, int v);

    public:
        template<typename T>
        explicit DepthFirstOrder(const GraphBase<T> &G);

        std::list<int> pre() const { return pre_; }
        std::list<int> post() const { return post_; }
        std::list<int> reversePost() const { return reversePost_; }
    };
}

template<typename T>
void algs4::DepthFirstOrder::dfs(const GraphBase<T> &G, int v) {
    pre_.push_back(v);
    marked[v] = true;
    for (const auto &e: G.adj(v)) {
        int w;
        if constexpr (std::is_same_v<std::decay_t<decltype(e)>, DirectedEdge>) w = e.to();
        else w = e;
        if (!marked[w])
            dfs(G, w);
    }
    post_.push_back(v);
    reversePost_.push_front(v);
}

template<typename T>
algs4::DepthFirstOrder::DepthFirstOrder(const GraphBase<T> &G) : marked(G.V()) {
    for (int v = 0; v < G.V(); ++v)
        if (!marked[v])
            dfs(G, v);
}


#endif //ALGS4_DEPTHFIRSTORDER_HPP
