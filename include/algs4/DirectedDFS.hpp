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

#ifndef ALGS4_DIRECTEDDFS_HPP
#define ALGS4_DIRECTEDDFS_HPP

#include <cassert>
#include <vector>

#include "Bag.hpp"
#include "Digraph.hpp"

namespace algs4 {
class DirectedDFS {
private:
    std::vector<bool> marked_;

    constexpr void dfs(const Digraph& G, int v) {
        marked_[v] = true;
        for (int w : G.adj(v))
            if (!marked_[w]) dfs(G, w);
    }

public:
    constexpr DirectedDFS(const Digraph& G, int s) : marked_(G.V()) {
        assert(s >= 0 && s < std::ssize(marked_));
        dfs(G, s);
    }

    constexpr DirectedDFS(const Digraph& G, const Bag<int>& sources) : marked_(G.V()) {
        assert(!sources.isEmpty());
        for (int s : sources) {
            assert(s >= 0 && s < std::ssize(marked_));
            if (!marked_[s]) dfs(G, s);
        }
    }

    constexpr bool marked(int v) const { return marked_[v]; }
};
}  // namespace algs4

#endif  // ALGS4_DIRECTEDDFS_HPP
