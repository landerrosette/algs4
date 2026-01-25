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

#ifndef ALGS4_DIGRAPH_HPP
#define ALGS4_DIGRAPH_HPP

#include <cassert>
#include <cstddef>

#include "GraphBase.hpp"

namespace algs4 {
class Digraph : public detail::GraphBase<int> {
public:
    constexpr explicit Digraph(int V) : GraphBase(V) {}

    explicit Digraph(std::istream& in) : GraphBase(in) {
        std::ptrdiff_t E;
        in >> E;
        assert(E >= 0);
        for (decltype(E) i = 0; i < E; ++i) {
            int v, w;
            in >> v >> w;
            addEdge(v, w);
        }
    }

    constexpr void addEdge(int v, int w) {
        assert(v >= 0 && v < V_);
        assert(w >= 0 && w < V_);
        adj_[v].add(w);
        ++E_;
    }

    constexpr Digraph reverse() const {
        Digraph R(V_);
        for (int v = 0; v < V_; ++v)
            for (int w : adj(v)) R.addEdge(w, v);
        return R;
    }
};
}  // namespace algs4

#endif  // ALGS4_DIGRAPH_HPP
