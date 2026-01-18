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

#ifndef ALGS4_EDGE_HPP
#define ALGS4_EDGE_HPP

#include <cassert>
#include <iomanip>
#include <ostream>

#include "EdgeBase.hpp"

namespace algs4 {
    class Edge : public EdgeBase {
        friend std::ostream &operator<<(std::ostream &os, const Edge &e);

    public:
        constexpr Edge() = default;
        constexpr Edge(int v, int w, double weight) : EdgeBase(v, w, weight) {}

        constexpr int either() const { return v_; }
        constexpr int other(int vertex) const;
    };

    std::ostream &operator<<(std::ostream &os, const Edge &e);
}

constexpr int algs4::Edge::other(int vertex) const {
    if (vertex == v_) return w_;
    else if (vertex == w_) return v_;
    else
        assert(false);
}

inline std::ostream &algs4::operator<<(std::ostream &os, const Edge &e) {
    return os << e.v_ << "-" << e.w_ << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
}

#endif // ALGS4_EDGE_HPP
