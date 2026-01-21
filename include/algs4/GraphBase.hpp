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

#ifndef ALGS4_GRAPHBASE_HPP
#define ALGS4_GRAPHBASE_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <istream>
#include <ostream>
#include <vector>

#include "Bag.hpp"

namespace algs4 {
    namespace detail {
        template<std::semiregular EdgeType>
        class GraphBase {
        protected:
            int V_;                           // number of vertices
            std::ptrdiff_t E_;                // number of edges
            std::vector<Bag<EdgeType> > adj_; // adjacency lists

            constexpr explicit GraphBase(int V) : V_(V), E_(0), adj_(V) { assert(V >= 0); }
            explicit GraphBase(std::istream &in);
            constexpr ~GraphBase() = default;
            constexpr GraphBase(const GraphBase &) = default;
            constexpr GraphBase &operator=(const GraphBase &) = default;
            constexpr GraphBase(GraphBase &&) noexcept = default;
            constexpr GraphBase &operator=(GraphBase &&) noexcept = default;

        public:
            constexpr int V() const { return V_; }
            constexpr auto E() const { return E_; }
            constexpr const Bag<EdgeType> &adj(int v) const &;
        };
    }
}

template<std::semiregular EdgeType>
algs4::detail::GraphBase<EdgeType>::GraphBase(std::istream &in) : GraphBase([&in] {
    int i;
    in >> i;
    return i;
}()) {}

template<std::semiregular EdgeType>
constexpr const algs4::Bag<EdgeType> &algs4::detail::GraphBase<EdgeType>::adj(int v) const & {
    assert(v >= 0 && v < V());
    return adj_[v];
}

template<std::semiregular EdgeType>
std::ostream &operator<<(std::ostream &os, const algs4::detail::GraphBase<EdgeType> &G) {
    os << G.V() << " vertices, " << G.E() << " edges" << std::endl;
    for (int v = 0; v < G.V(); ++v) {
        os << v << ": ";
        for (const EdgeType &w: G.adj(v)) os << w << " ";
        os << std::endl;
    }
    return os;
}

#endif // ALGS4_GRAPHBASE_HPP
