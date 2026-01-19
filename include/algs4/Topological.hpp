/*
 * Copyright (C) 2024-2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#include <utility>

#include "DepthFirstOrder.hpp"
#include "DirectedCycle.hpp"
#include "GraphBase.hpp"
#include "Stack.hpp"

namespace algs4 {
    class Topological {
    private:
        Stack<int> order_; // topological order

    public:
        template<typename EdgeType>
        constexpr explicit Topological(const GraphBase<EdgeType> &G);

        constexpr const auto &order() const & { return order_; }
        constexpr auto &&order() && { return std::move(order_); }
        constexpr bool isDAG() const { return !order_.isEmpty(); }
    };
}

template<typename EdgeType>
constexpr algs4::Topological::Topological(const GraphBase<EdgeType> &G) {
    if (!DirectedCycle(G).hasCycle())
        order_ = DepthFirstOrder(G).reversePost();
}

#endif // ALGS4_TOPOLOGICAL_HPP
