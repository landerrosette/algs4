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

#ifndef ALGS4_SP_HPP
#define ALGS4_SP_HPP

#include <cassert>
#include <limits>
#include <vector>

#include "DirectedEdge.hpp"
#include "EdgeWeightedDigraph.hpp"
#include "Stack.hpp"

namespace algs4 {
class SP {
protected:
    std::vector<DirectedEdge> edgeTo_;
    std::vector<double> distTo_;

    constexpr SP(const EdgeWeightedDigraph& G, int s)
        : edgeTo_(G.V()), distTo_(G.V(), std::numeric_limits<double>::infinity()) {
        assert(s >= 0 && s < std::ssize(distTo_));
        distTo_[s] = 0.0;
    }

    constexpr SP(const SP&) = default;
    constexpr SP& operator=(const SP&) = default;
    constexpr SP(SP&&) noexcept = default;
    constexpr SP& operator=(SP&&) noexcept = default;

    constexpr void relax(const EdgeWeightedDigraph& G, int v) {
        for (const auto& e : G.adj(v)) {
            int w = e.to();
            if (distTo_[w] > distTo_[v] + e.weight()) {
                distTo_[w] = distTo_[v] + e.weight();
                edgeTo_[w] = e;
                onEdgeRelaxed(G, v, e, w);
            }
            afterRelaxation(G, v, e, w);
        }
    }

    virtual constexpr void onEdgeRelaxed(const EdgeWeightedDigraph& G, int v, const DirectedEdge& e, int w) {}
    virtual constexpr void afterRelaxation(const EdgeWeightedDigraph& G, int v, const DirectedEdge& e, int w) {}

public:
    virtual constexpr ~SP() = default;

    constexpr double distTo(int v) const {
        assert(v >= 0 && v < std::ssize(distTo_));
        return distTo_[v];
    }

    constexpr bool hasPathTo(int v) const {
        assert(v >= 0 && v < std::ssize(distTo_));
        return distTo_[v] < std::numeric_limits<double>::infinity();
    }

    constexpr Stack<DirectedEdge> pathTo(int v) const {
        assert(v >= 0 && v < std::ssize(distTo_));
        if (!hasPathTo(v)) return {};
        Stack<DirectedEdge> path;
        for (auto e = edgeTo_[v]; e; e = edgeTo_[e.from()]) path.push(e);
        return path;
    }
};
}  // namespace algs4

#endif  // ALGS4_SP_HPP
