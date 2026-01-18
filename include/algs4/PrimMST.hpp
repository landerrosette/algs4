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

#ifndef ALGS4_PRIMMST_HPP
#define ALGS4_PRIMMST_HPP

#include <limits>
#include <vector>

#include "EdgeWeightedGraph.hpp"
#include "IndexMinPQ.hpp"
#include "MST.hpp"

namespace algs4 {
    class PrimMST : public MST {
    private:
        std::vector<Edge> edgeTo_;   // shortest edge from tree vertex
        std::vector<double> distTo_; // distTo_[w] = edgeTo_[w].weight()
        std::vector<bool> marked_;   // true if v on tree
        IndexMinPQ<double> pq_;      // eligible crossing edges

        constexpr void visit(const EdgeWeightedGraph &G, int v);

    public:
        constexpr explicit PrimMST(const EdgeWeightedGraph &G);

        Queue<Edge> edges() const override;
    };
}

constexpr void algs4::PrimMST::visit(const EdgeWeightedGraph &G, int v) {
    marked_[v] = true;
    for (const auto &e: G.adj(v)) {
        int w = e.other(v);
        if (marked_[w]) continue; // v-w is ineligible.
        if (e.weight() < distTo_[w]) {
            // Edge e is new best connection from tree to w.
            edgeTo_[w] = e;
            distTo_[w] = e.weight();
            if (pq_.contains(w)) pq_.change(w, distTo_[w]);
            else pq_.insert(w, distTo_[w]);
        }
    }
}

constexpr algs4::PrimMST::PrimMST(const EdgeWeightedGraph &G)
    : edgeTo_(G.V()), distTo_(G.V(), std::numeric_limits<double>::infinity()), marked_(G.V()), pq_(G.V()) {
    distTo_[0] = 0.0;
    pq_.insert(0, 0.0);
    while (!pq_.isEmpty())
        visit(G, static_cast<int>(pq_.delMin()));
}

inline algs4::Queue<algs4::Edge> algs4::PrimMST::edges() const {
    Queue<Edge> mst;
    for (int v = 0; v < std::ssize(edgeTo_); ++v)
        if (const auto &e = edgeTo_[v])
            mst.enqueue(e);
    return mst;
}

#endif // ALGS4_PRIMMST_HPP
