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

#ifndef ALGS4_KRUSKALMST_HPP
#define ALGS4_KRUSKALMST_HPP

#include "EdgeWeightedGraph.hpp"
#include "MST.hpp"
#include "MinPQ.hpp"
#include "Queue.hpp"
#include "UF.hpp"

namespace algs4 {
class KruskalMST : public MST {
private:
    Queue<Edge> mst_;

public:
    explicit KruskalMST(const EdgeWeightedGraph& G) {
        MinPQ<Edge> pq;
        for (const auto& e : G.edges()) pq.insert(e);
        UF uf(G.V());
        while (!pq.isEmpty() && std::ssize(mst_) < G.V() - 1) {
            auto e = pq.delMin();
            int v = e.either(), w = e.other(v);
            if (uf.connected(v, w)) continue;
            uf.unionize(v, w);
            mst_.enqueue(e);
        }
    }

    Queue<Edge> edges() const override { return mst_; }
};
}  // namespace algs4

#endif  // ALGS4_KRUSKALMST_HPP
