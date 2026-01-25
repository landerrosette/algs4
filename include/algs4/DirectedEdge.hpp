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

#ifndef ALGS4_DIRECTEDEDGE_HPP
#define ALGS4_DIRECTEDEDGE_HPP

#include <iomanip>
#include <ostream>

#include "EdgeBase.hpp"

namespace algs4 {
class DirectedEdge : public detail::EdgeBase {
public:
    constexpr DirectedEdge() = default;
    constexpr DirectedEdge(int v, int w, double weight) : EdgeBase(v, w, weight) {}

    constexpr int from() const { return v_; }
    constexpr int to() const { return w_; }

    friend std::ostream& operator<<(std::ostream& os, const DirectedEdge& e) {
        return os << e.v_ << "->" << e.w_ << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
    }
};
}  // namespace algs4

#endif  // ALGS4_DIRECTEDEDGE_HPP
