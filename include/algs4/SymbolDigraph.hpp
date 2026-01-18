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

#ifndef ALGS4_SYMBOLDIGRAPH_HPP
#define ALGS4_SYMBOLDIGRAPH_HPP

#include <cassert>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "Digraph.hpp"
#include "RedBlackBST.hpp"
#include "ST.hpp"

namespace algs4 {
    template<std::derived_from<algs4::ST<std::string, int> > STType = RedBlackBST<std::string, int> >
    class SymbolDigraph {
    private:
        STType st_;                     // symbol -> index
        std::vector<std::string> keys_; // index -> symbol
        std::unique_ptr<Digraph> G_;    // the graph

    public:
        SymbolDigraph(const std::filesystem::path &filepath, char sp);

        std::string_view name(int v) const &;
        const Digraph &G() const & { return *G_; }
    };
}

template<std::derived_from<algs4::ST<std::string, int> > STType>
algs4::SymbolDigraph<STType>::SymbolDigraph(const std::filesystem::path &filepath, char sp) {
    std::ifstream in(filepath);
    if (!in.is_open())
        throw std::invalid_argument("Cannot open file: " + filepath.string());
    // First pass builds the index by reading strings to associate each distinct string with an index.
    for (std::string line; std::getline(in, line);) {
        std::string name;
        for (std::istringstream iss(line); std::getline(iss, name, sp);)
            if (!st_.contains(name))
                st_.put(name, static_cast<int>(st_.size()));
    }
    keys_.resize(st_.size()); // Inverted index to get string keys is an array.
    for (const auto &name: st_.keys())
        keys_[*st_.get(name)] = name;

    G_ = std::make_unique<Digraph>(st_.size());
    in = std::ifstream(filepath);
    if (!in.is_open())
        throw std::invalid_argument("Cannot open file: " + filepath.string());
    // Second pass builds the graph by connecting the first vertex on each line to all the others.
    for (std::string line; std::getline(in, line);) {
        std::string name;
        std::istringstream iss(line);
        std::getline(iss, name, sp);
        int v = *st_.get(name);
        while (std::getline(iss, name, sp))
            G_->addEdge(v, *st_.get(name));
    }
}

template<std::derived_from<algs4::ST<std::string, int> > STType>
std::string_view algs4::SymbolDigraph<STType>::name(int v) const & {
    assert(v >= 0 && v < G_->V());
    return keys_[v];
}

#endif // ALGS4_SYMBOLDIGRAPH_HPP
