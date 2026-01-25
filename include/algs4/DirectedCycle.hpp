/*
 * Copyright (C) 2024-2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_DIRECTEDCYCLE_HPP
#define ALGS4_DIRECTEDCYCLE_HPP

#include <type_traits>
#include <utility>
#include <vector>

#include "DirectedEdge.hpp"
#include "GraphBase.hpp"
#include "Stack.hpp"

namespace algs4 {
template <std::semiregular EdgeType>
class DirectedCycle {
private:
    std::vector<bool> marked_;
    std::vector<EdgeType> edgeTo_;
    Stack<EdgeType> cycle_;
    std::vector<bool> onStack_;  // vertices on recursive call stack

    constexpr void dfs(const detail::GraphBase<EdgeType>& G, int v) {
        onStack_[v] = true;
        marked_[v] = true;
        for (const auto& e : G.adj(v)) {
            int w;
            if constexpr (std::is_same_v<std::remove_cvref_t<decltype(e)>, DirectedEdge>)
                w = e.to();
            else
                w = e;
            if (hasCycle())
                return;
            else if (!marked_[w]) {
                edgeTo_[w] = e;
                dfs(G, w);
            } else if (onStack_[w]) {
                if constexpr (std::is_same_v<std::remove_cvref_t<decltype(e)>, DirectedEdge>) {
                    auto x = e;
                    for (; x.from() != w; x = edgeTo_[x.from()]) cycle_.push(x);
                    cycle_.push(x);
                } else {
                    for (int x = v; x != w; x = edgeTo_[x]) cycle_.push(x);
                    cycle_.push(w);
                    cycle_.push(v);
                }
            }
        }
        onStack_[v] = false;
    }

public:
    constexpr explicit DirectedCycle(const detail::GraphBase<EdgeType>& G)
        : marked_(G.V()), edgeTo_(G.V()), onStack_(G.V()) {
        for (int v = 0; v < G.V(); ++v)
            if (!marked_[v]) dfs(G, v);
    }

    constexpr bool hasCycle() const { return !cycle_.isEmpty(); }
    constexpr const auto& cycle() const& { return cycle_; }
    constexpr auto&& cycle() && { return std::move(cycle_); }
};
}  // namespace algs4

#endif  // ALGS4_DIRECTEDCYCLE_HPP
