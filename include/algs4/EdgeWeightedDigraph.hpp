/*
 * Copyright (C) 2024-2026 landerrosette
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

#ifndef ALGS4_EDGEWEIGHTEDDIGRAPH_HPP
#define ALGS4_EDGEWEIGHTEDDIGRAPH_HPP

#include <cassert>
#include <cstddef>

#include "Bag.hpp"
#include "DirectedEdge.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class EdgeWeightedDigraph : public GraphBase<DirectedEdge> {
    public:
        constexpr explicit EdgeWeightedDigraph(int V) : GraphBase(V) {}
        explicit EdgeWeightedDigraph(std::istream &in);

        constexpr void addEdge(const DirectedEdge &e);
        constexpr Bag<DirectedEdge> edges() const;
    };
}

inline algs4::EdgeWeightedDigraph::EdgeWeightedDigraph(std::istream &in) : GraphBase(in) {
    std::ptrdiff_t E;
    in >> E;
    assert(E >= 0);
    for (decltype(E) i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(DirectedEdge(v, w, weight));
    }
}

constexpr void algs4::EdgeWeightedDigraph::addEdge(const DirectedEdge &e) {
    adj_[e.from()].add(e);
    ++E_;
}

constexpr algs4::Bag<algs4::DirectedEdge> algs4::EdgeWeightedDigraph::edges() const {
    Bag<DirectedEdge> bag;
    for (int v = 0; v < V_; ++v)
        for (const auto &e: adj(v))
            bag.add(e);
    return bag;
}

#endif // ALGS4_EDGEWEIGHTEDDIGRAPH_HPP
