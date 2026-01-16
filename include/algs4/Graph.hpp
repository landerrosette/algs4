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

#ifndef ALGS4_GRAPH_HPP
#define ALGS4_GRAPH_HPP

#include <cassert>
#include <cstddef>

#include "GraphBase.hpp"

namespace algs4 {
    class Graph : public GraphBase<int> {
    public:
        constexpr explicit Graph(int V) : GraphBase(V) {}
        explicit Graph(std::istream &in);

        constexpr void addEdge(int v, int w);
    };
}

inline algs4::Graph::Graph(std::istream &in) : GraphBase(in) {
    std::ptrdiff_t E;
    in >> E;
    assert(E >= 0);
    for (decltype(E) i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

constexpr void algs4::Graph::addEdge(int v, int w) {
    assert(v >= 0 && v < V_);
    assert(w >= 0 && w < V_);
    adj_[v].push_back(w);
    adj_[w].push_back(v);
    ++E_;
}

#endif // ALGS4_GRAPH_HPP
