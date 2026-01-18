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

#ifndef ALGS4_CCBASE_HPP
#define ALGS4_CCBASE_HPP

#include <cassert>
#include <vector>

#include "GraphBase.hpp"

namespace algs4 {
    class CCBase {
    protected:
        std::vector<bool> marked_;
        std::vector<int> id_;
        int count_ = 0;

        constexpr explicit CCBase(const GraphBase<int> &G) : marked_(G.V()), id_(G.V()) {}
        constexpr ~CCBase() = default;
        constexpr CCBase(const CCBase &) = default;
        constexpr CCBase &operator=(const CCBase &) = default;
        constexpr CCBase(CCBase &&) noexcept = default;
        constexpr CCBase &operator=(CCBase &&) noexcept = default;

        constexpr void dfs(const GraphBase<int> &G, int v);

    public:
        constexpr bool connected(int v, int w) const;
        constexpr int id(int v) const;
        constexpr int count() const { return count_; }
    };
}

constexpr void algs4::CCBase::dfs(const GraphBase<int> &G, int v) {
    marked_[v] = true;
    id_[v] = count_;
    for (int w: G.adj(v))
        if (!marked_[w]) dfs(G, w);
}

constexpr bool algs4::CCBase::connected(int v, int w) const {
    assert(v >= 0 && v < std::ssize(marked_));
    assert(w >= 0 && w < std::ssize(marked_));
    return id_[v] == id_[w];
}

constexpr int algs4::CCBase::id(int v) const {
    assert(v >= 0 && v < std::ssize(marked_));
    return id_[v];
}

#endif // ALGS4_CCBASE_HPP
