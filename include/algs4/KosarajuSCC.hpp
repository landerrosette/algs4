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

#ifndef ALGS4_KOSARAJUSCC_HPP
#define ALGS4_KOSARAJUSCC_HPP

#include "CCBase.hpp"
#include "DepthFirstOrder.hpp"
#include "Digraph.hpp"

namespace algs4 {
    class KosarajuSCC : public CCBase {
    public:
        explicit KosarajuSCC(const Digraph &G);

        bool stronglyConnected(int v, int w) const { return connected(v, w); }
    };
}

inline algs4::KosarajuSCC::KosarajuSCC(const Digraph &G) : CCBase(G) {
    DepthFirstOrder order(G.reverse());
    for (int s: order.reversePost()) {
        if (!marked_[s]) {
            dfs(G, s);
            ++count_;
        }
    }
}

#endif // ALGS4_KOSARAJUSCC_HPP
