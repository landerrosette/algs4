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

#ifndef ALGS4_SUBSTRSEARCHER_HPP
#define ALGS4_SUBSTRSEARCHER_HPP

#include <cstddef>
#include <string_view>

namespace algs4 {
    class SubstrSearcher {
    protected:
        constexpr SubstrSearcher() = default;
        constexpr SubstrSearcher(const SubstrSearcher &) = default;
        constexpr SubstrSearcher &operator=(const SubstrSearcher &) = default;
        constexpr SubstrSearcher(SubstrSearcher &&) noexcept = default;
        constexpr SubstrSearcher &operator=(SubstrSearcher &&) noexcept = default;

    public:
        virtual constexpr ~SubstrSearcher() = default;

        virtual constexpr std::ptrdiff_t search(std::string_view txt) const = 0;
    };
}

#endif // ALGS4_SUBSTRSEARCHER_HPP
