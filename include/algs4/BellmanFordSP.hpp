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

#ifndef ALGS4_BELLMANFORDSP_HPP
#define ALGS4_BELLMANFORDSP_HPP

#include <utility>
#include <vector>

#include "DirectedCycle.hpp"
#include "Queue.hpp"
#include "SP.hpp"
#include "Stack.hpp"

namespace algs4 {
class BellmanFordSP : public SP {
private:
    std::vector<bool> onQ_;      // Is this vertex on the queue?
    Queue<int> queue_;           // vertices being relaxed
    int cost_ = 0;               // number of calls to relax()
    Stack<DirectedEdge> cycle_;  // negative cycle in edgeTo_[]

    void onEdgeRelaxed(const EdgeWeightedDigraph& G, int v, const DirectedEdge& e, int w) override {
        if (!onQ_[w]) {
            queue_.enqueue(w);
            onQ_[w] = true;
        }
    }

    void afterRelaxation(const EdgeWeightedDigraph& G, int v, const DirectedEdge& e, int w) override {
        if (cost_++ % G.V() == 0) findNegativeCycle();
    }

    void findNegativeCycle() {
        int V = static_cast<int>(std::ssize(edgeTo_));
        EdgeWeightedDigraph spt(V);
        for (int v = 0; v < V; ++v)
            if (edgeTo_[v]) spt.addEdge(edgeTo_[v]);
        cycle_ = DirectedCycle(spt).cycle();
    }

public:
    BellmanFordSP(const EdgeWeightedDigraph& G, int s) : SP(G, s), onQ_(G.V()) {
        queue_.enqueue(s);
        onQ_[s] = true;
        while (!queue_.isEmpty() && !hasNegativeCycle()) {
            int v = queue_.dequeue();
            onQ_[v] = false;
            relax(G, v);
        }
    }

    bool hasNegativeCycle() const { return !cycle_.isEmpty(); }

    const Stack<DirectedEdge>& negativeCycle() const& { return cycle_; }

    Stack<DirectedEdge>&& negativeCycle() && { return std::move(cycle_); }
};
}  // namespace algs4

#endif  // ALGS4_BELLMANFORDSP_HPP
