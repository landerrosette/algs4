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

#ifndef ALGS4_PATHS_HPP
#define ALGS4_PATHS_HPP

#include <cassert>
#include <vector>

#include "Graph.hpp"
#include "Stack.hpp"

namespace algs4 {
    class Paths {
    protected:
        std::vector<bool> marked_; // Has dfs() been called for this vertex?
        std::vector<int> edgeTo_;  // last vertex on known path for this vertex
        int s_;                    // source

        constexpr Paths(const Graph &G, int s);

        constexpr Paths(const Paths &) = default;
        constexpr Paths &operator=(const Paths &) = default;
        constexpr Paths(Paths &&) noexcept = default;
        constexpr Paths &operator=(Paths &&) noexcept = default;

    public:
        virtual constexpr ~Paths() = default;

        constexpr bool hasPathTo(int v) const { return marked_[v]; }
        constexpr Stack<int> pathTo(int v) const;
    };
}

constexpr algs4::Paths::Paths(const Graph &G, int s) : marked_(G.V()), edgeTo_(G.V()), s_(s) {
    assert(s >= 0 && s < std::ssize(marked_));
}

constexpr algs4::Stack<int> algs4::Paths::pathTo(int v) const {
    assert(v >= 0 && v < std::ssize(marked_));
    if (!hasPathTo(v)) return {};
    Stack<int> path;
    for (int x = v; x != s_; x = edgeTo_[x])
        path.push(x);
    path.push(s_);
    return path;
}

#endif // ALGS4_PATHS_HPP
