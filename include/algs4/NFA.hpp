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

#ifndef ALGS4_NFA_HPP
#define ALGS4_NFA_HPP

#include <string>
#include <string_view>
#include <utility>

#include "Bag.hpp"
#include "Digraph.hpp"
#include "DirectedDFS.hpp"
#include "Stack.hpp"

namespace algs4 {
    class NFA {
    private:
        std::string re_; // match transitions
        int M_;          // number of states
        Digraph G_;      // epsilon transitions

    public:
        constexpr explicit NFA(std::string regexp);

        constexpr bool recognizes(std::string_view txt) const;
    };
}

constexpr algs4::NFA::NFA(std::string regexp)
    : re_(std::move(regexp)), M_(static_cast<int>(std::ssize(re_))), G_(M_ + 1) {
    Stack<int> ops;
    for (int i = 0; i < M_; ++i) {
        int lp = i; // left position
        if (re_[i] == '(' || re_[i] == '|')
            ops.push(i);
        else if (re_[i] == ')') {
            int orPos = ops.pop();
            if (re_[orPos] == '|') {
                lp = ops.pop();
                G_.addEdge(lp, orPos + 1);
                G_.addEdge(orPos, i);
            } else lp = orPos;
        }
        if (i < M_ - 1 && re_[i + 1] == '*') {
            // lookahead
            G_.addEdge(lp, i + 1);
            G_.addEdge(i + 1, lp);
        }
        if (re_[i] == '(' || re_[i] == '*' || re_[i] == ')')
            G_.addEdge(i, i + 1);
    }
}

constexpr bool algs4::NFA::recognizes(std::string_view txt) const {
    Bag<int> pc;
    DirectedDFS dfs(G_, 0);
    for (int v = 0; v < G_.V(); ++v)
        if (dfs.marked(v)) pc.add(v);

    for (char c: txt) {
        Bag<int> match;
        for (int v: pc)
            if (v < M_)
                if (re_[v] == c || re_[v] == '.') match.add(v + 1);
        pc = Bag<int>();
        dfs = DirectedDFS(G_, match);
        for (int v = 0; v < G_.V(); ++v)
            if (dfs.marked(v)) pc.add(v);
    }
    for (int v: pc) if (v == M_) return true;
    return false;
}

#endif // ALGS4_NFA_HPP
