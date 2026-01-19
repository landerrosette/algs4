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

#ifndef ALGS4_MAXPQ_HPP
#define ALGS4_MAXPQ_HPP

#include <concepts>
#include <functional>

#include "PQBase.hpp"

namespace algs4 {
    template<std::totally_ordered Key>
    class MaxPQ : public PQBase<Key, std::less<Key> > {
    public:
        constexpr Key delMax() { return this->delTop(); }
    };
}

#endif // ALGS4_MAXPQ_HPP
