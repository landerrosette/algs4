/*
 * Copyright (C) 2024 landerrosette
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ALGS4_DEPTHFIRSTORDER_HPP
#define ALGS4_DEPTHFIRSTORDER_HPP

#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>

#include "DirectedEdge.hpp"
#include "GraphBase.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

namespace algs4 {
    class DepthFirstOrder {
    private:
        std::vector<bool> marked_;
        Queue<int> pre_, post_;
        Stack<int> reversePost_;

        template<typename EdgeType>
        void dfs(const GraphBase<EdgeType> &G, int v);

    public:
        template<typename EdgeType>
        explicit DepthFirstOrder(const GraphBase<EdgeType> &G);

        const auto &pre() const & { return pre_; }
        auto &&pre() && { return std::move(pre_); }
        const auto &post() const & { return post_; }
        auto &&post() && { return std::move(post_); }
        const auto &reversePost() const & { return reversePost_; }
        auto &&reversePost() && { return std::move(reversePost_); }
    };
}

template<typename EdgeType>
void algs4::DepthFirstOrder::dfs(const GraphBase<EdgeType> &G, int v) {
    pre_.enqueue(v);
    marked_[v] = true;
    for (const auto &e: G.adj(v)) {
        int w;
        if constexpr (std::same_as<std::remove_cvref_t<decltype(e)>, DirectedEdge>) w = e.to();
        else w = e;
        if (!marked_[w])
            dfs(G, w);
    }
    post_.enqueue(v);
    reversePost_.push(v);
}

template<typename EdgeType>
algs4::DepthFirstOrder::DepthFirstOrder(const GraphBase<EdgeType> &G) : marked_(G.V()) {
    for (int v = 0; v < G.V(); ++v)
        if (!marked_[v]) dfs(G, v);
}

#endif // ALGS4_DEPTHFIRSTORDER_HPP
