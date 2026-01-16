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

#ifndef ALGS4_EDGEWEIGHTEDGRAPH_HPP
#define ALGS4_EDGEWEIGHTEDGRAPH_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

#include "Edge.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class EdgeWeightedGraph : public GraphBase<Edge> {
    public:
        constexpr explicit EdgeWeightedGraph(int V) : GraphBase(V) {}
        explicit EdgeWeightedGraph(std::istream &in);

        constexpr void addEdge(const Edge &e);
        constexpr std::vector<Edge> edges() const;
    };
}

inline algs4::EdgeWeightedGraph::EdgeWeightedGraph(std::istream &in) : GraphBase(in) {
    std::ptrdiff_t E;
    in >> E;
    assert(E >= 0);
    for (decltype(E) i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(Edge(v, w, weight));
    }
}

constexpr void algs4::EdgeWeightedGraph::addEdge(const Edge &e) {
    int v = e.either(), w = e.other(v);
    adj_[v].push_back(e);
    adj_[w].push_back(e);
    ++E_;
}

constexpr std::vector<algs4::Edge> algs4::EdgeWeightedGraph::edges() const {
    std::vector<Edge> bag;
    for (int v = 0; v < V_; ++v)
        for (const auto &e: adj(v))
            if (e.other(v) > v)
                bag.push_back(e);
    std::ranges::reverse(bag);
    return bag;
}

#endif // ALGS4_EDGEWEIGHTEDGRAPH_HPP
