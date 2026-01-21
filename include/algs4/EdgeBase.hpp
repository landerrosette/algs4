/*
 * Copyright (C) 2025-2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_EDGEBASE_HPP
#define ALGS4_EDGEBASE_HPP

#include <cassert>
#include <compare>
#include <limits>

namespace algs4 {
    namespace detail {
        class EdgeBase {
        protected:
            int v_{}, w_{};
            double weight_ = std::numeric_limits<double>::quiet_NaN();

            constexpr EdgeBase() = default;
            constexpr EdgeBase(int v, int w, double weight);
            constexpr ~EdgeBase() = default;
            constexpr EdgeBase(const EdgeBase &) = default;
            constexpr EdgeBase &operator=(const EdgeBase &) = default;
            constexpr EdgeBase(EdgeBase &&) noexcept = default;
            constexpr EdgeBase &operator=(EdgeBase &&) noexcept = default;

        public:
            constexpr double weight() const { return weight_; }
            constexpr explicit operator bool() const { return weight_ == weight_; }
        };

        constexpr auto operator<=>(const EdgeBase &l, const EdgeBase &r) { return l.weight() <=> r.weight(); }
        constexpr bool operator==(const EdgeBase &l, const EdgeBase &r) { return l.weight() == r.weight(); }
    }
}

constexpr algs4::detail::EdgeBase::EdgeBase(int v, int w, double weight) : v_(v), w_(w), weight_(weight) {
    assert(v >= 0);
    assert(w >= 0);
    assert(weight == weight);
}

#endif // ALGS4_EDGEBASE_HPP
