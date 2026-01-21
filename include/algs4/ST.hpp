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

#ifndef ALGS4_ST_HPP
#define ALGS4_ST_HPP

#include <concepts>
#include <cstddef>
#include <utility>

#include "Queue.hpp"

namespace algs4 {
    template<std::copyable Key, std::movable Value>
    class ST {
    protected:
        constexpr ST() = default;
        constexpr ST(const ST &) = default;
        constexpr ST &operator=(const ST &) = default;
        constexpr ST(ST &&) noexcept = default;
        constexpr ST &operator=(ST &&) noexcept = default;

    public:
        virtual constexpr ~ST() = default;

        virtual constexpr void put(Key key, Value val) = 0;
        virtual constexpr const Value *get(const Key &key) const = 0;
        constexpr Value *get(const Key &key) { return const_cast<Value *>(std::as_const(*this).get(key)); }
        virtual constexpr void remove(const Key &key) = 0;
        constexpr bool contains(const Key &key) const { return get(key) != nullptr; }
        constexpr bool isEmpty() const { return size() == 0; }
        virtual constexpr std::ptrdiff_t size() const = 0;
        virtual Queue<Key> keys() const = 0;
    };
}

#endif // ALGS4_ST_HPP
