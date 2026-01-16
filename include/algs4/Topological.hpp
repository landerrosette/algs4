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
        constexpr explicit Topological(const GraphBase<EdgeType> &G);

        constexpr auto order() const & { return std::views::all(order_); }
        constexpr bool isDAG() const { return !order_.empty(); }
    };
}

template<typename EdgeType>
constexpr algs4::Topological::Topological(const GraphBase<EdgeType> &G) {
    DirectedCycle cyclefinder(G);
    if (!cyclefinder.hasCycle()) {
        DepthFirstOrder dfs(G);
        auto reversePost = dfs.reversePost();
        order_ = {reversePost.begin(), reversePost.end()};
    }
}

#endif // ALGS4_TOPOLOGICAL_HPP
