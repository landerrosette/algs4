/*
 * Copyright (C) 2026 landerrosette
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

#ifndef ALGS4_BAG_HPP
#define ALGS4_BAG_HPP

#include <concepts>
#include <utility>
#include <vector>

#include "IteratorWrapper.hpp"

namespace algs4 {
    template<typename T>
    class Bag {
    private:
        std::vector<T> a_;

    public:
        using iterator = internal::IteratorWrapper<std::vector<T>, true, false>;
        using const_iterator = internal::IteratorWrapper<std::vector<T>, true, true>;

        constexpr bool isEmpty() const { return a_.empty(); }
        constexpr std::ptrdiff_t size() const { return std::ssize(a_); }

        template<typename U> requires std::constructible_from<T, U>
        constexpr void add(U &&item) { a_.emplace_back(std::forward<U>(item)); }

        constexpr iterator begin() { return iterator(a_.rbegin()); }
        constexpr iterator end() { return iterator(a_.rend()); }
        constexpr const_iterator begin() const { return const_iterator(a_.rbegin()); }
        constexpr const_iterator end() const { return const_iterator(a_.rend()); }
        constexpr const_iterator cbegin() const { return const_iterator(a_.crbegin()); }
        constexpr const_iterator cend() const { return const_iterator(a_.crend()); }
    };
}

#endif // ALGS4_BAG_HPP
