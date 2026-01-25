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

#ifndef ALGS4_BREADTHFIRSTPATHS_HPP
#define ALGS4_BREADTHFIRSTPATHS_HPP

#include "Paths.hpp"
#include "Queue.hpp"

namespace algs4 {
class BreadthFirstPaths : public Paths {
private:
    void bfs(const Graph& G, int s) {
        Queue<int> queue;
        marked_[s] = true;
        queue.enqueue(s);
        while (!queue.isEmpty()) {
            int v = queue.dequeue();
            for (int w : G.adj(v)) {
                if (!marked_[w]) {
                    edgeTo_[w] = v;
                    marked_[w] = true;
                    queue.enqueue(w);
                }
            }
        }
    }

public:
    BreadthFirstPaths(const Graph& G, int s) : Paths(G, s) { bfs(G, s); }
};
}  // namespace algs4

#endif  // ALGS4_BREADTHFIRSTPATHS_HPP
