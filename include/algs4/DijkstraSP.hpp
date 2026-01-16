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

#ifndef ALGS4_DIJKSTRASP_HPP
#define ALGS4_DIJKSTRASP_HPP

#include "IndexMinPQ.hpp"
#include "SP.hpp"

namespace algs4 {
    class DijkstraSP : public SP {
    private:
        IndexMinPQ<double> pq_;

        constexpr void onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

    public:
        constexpr DijkstraSP(const EdgeWeightedDigraph &G, int s);
    };
}

constexpr void algs4::DijkstraSP::onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (pq_.contains(w)) pq_.change(w, distTo_[w]);
    else pq_.insert(w, distTo_[w]);
}

constexpr algs4::DijkstraSP::DijkstraSP(const EdgeWeightedDigraph &G, int s) : SP(G, s), pq_(G.V()) {
    pq_.insert(s, 0.0);
    while (!pq_.isEmpty())
        relax(G, static_cast<int>(pq_.delMin()));
}

#endif // ALGS4_DIJKSTRASP_HPP
