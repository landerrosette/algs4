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

#ifndef ALGS4_CC_HPP
#define ALGS4_CC_HPP

#include "CCBase.hpp"
#include "Graph.hpp"

namespace algs4 {
    class CC : public CCBase {
    public:
        constexpr explicit CC(const Graph &G);
    };
}

constexpr algs4::CC::CC(const Graph &G) : CCBase(G) {
    for (int s = 0; s < G.V(); ++s) {
        if (!marked_[s]) {
            dfs(G, s);
            ++count_;
        }
    }
}

#endif // ALGS4_CC_HPP
