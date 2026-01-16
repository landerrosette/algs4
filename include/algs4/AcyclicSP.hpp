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

#ifndef ALGS4_ACYCLICSP_HPP
#define ALGS4_ACYCLICSP_HPP

#include "SP.hpp"
#include "Topological.hpp"

namespace algs4 {
    class AcyclicSP : public SP {
    public:
        constexpr AcyclicSP(const EdgeWeightedDigraph &G, int s);
    };
}

constexpr algs4::AcyclicSP::AcyclicSP(const EdgeWeightedDigraph &G, int s) : SP(G, s) {
    Topological top(G);
    for (int v: top.order())
        relax(G, v);
}

#endif // ALGS4_ACYCLICSP_HPP
