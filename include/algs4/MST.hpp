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

#ifndef ALGS4_MST_HPP
#define ALGS4_MST_HPP

#include <vector>

#include "Edge.hpp"

namespace algs4 {
    class MST {
    protected:
        constexpr MST() = default;
        constexpr MST(const MST &) = default;
        constexpr MST &operator=(const MST &) = default;
        constexpr MST(MST &&) noexcept = default;
        constexpr MST &operator=(MST &&) noexcept = default;

    public:
        virtual constexpr ~MST() = default;

        virtual constexpr std::vector<Edge> edges() const = 0;
        constexpr double weight() const;
    };
}

constexpr double algs4::MST::weight() const {
    double weight = 0.0;
    for (const auto &e: edges())
        weight += e.weight();
    return weight;
}

#endif // ALGS4_MST_HPP
