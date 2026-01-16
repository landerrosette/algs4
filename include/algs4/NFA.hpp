#ifndef ALGS4_NFA_HPP
#define ALGS4_NFA_HPP

#include <stack>
#include <string>
#include <string_view>
#include <vector>

#include "Digraph.hpp"
#include "DirectedDFS.hpp"

namespace algs4 {
    class NFA {
    private:
        std::string re_; // match transitions
        int M_;          // number of states
        Digraph G_;      // epsilon transitions

    public:
        explicit NFA(std::string regexp);

        bool recognizes(std::string_view txt) const;
    };
}

inline algs4::NFA::NFA(std::string regexp) : re_(std::move(regexp)), M_(static_cast<int>(std::ssize(re_))), G_(M_ + 1) {
    std::stack<int> ops;
    for (int i = 0; i < M_; ++i) {
        int lp = i; // left position
        if (re_[i] == '(' || re_[i] == '|') ops.push(i);
        else if (re_[i] == ')') {
            int orPos = ops.top();
            ops.pop();
            if (re_[orPos] == '|') {
                lp = ops.top();
                ops.pop();
                G_.addEdge(lp, orPos + 1);
                G_.addEdge(orPos, i);
            } else lp = orPos;
        }
        if (i < M_ - 1 && re_[i + 1] == '*') {
            G_.addEdge(lp, i + 1);
            G_.addEdge(i + 1, lp);
        } // lookahead
        if (re_[i] == '(' || re_[i] == '*' || re_[i] == ')') G_.addEdge(i, i + 1);
    }
}

inline bool algs4::NFA::recognizes(std::string_view txt) const {
    std::vector<int> pc;
    DirectedDFS dfs(G_, 0);
    for (int v = 0; v < G_.V(); ++v)
        if (dfs.marked(v)) pc.push_back(v);

    // Compute possible NFA states for txt[i+1].
    for (char c: txt) {
        std::vector<int> match;
        for (int v: pc)
            if (v < M_)
                if (re_[v] == c || re_[v] == '.') match.push_back(v + 1);
        pc.clear();
        dfs = DirectedDFS(G_, match);
        for (int v = 0; v < G_.V(); ++v)
            if (dfs.marked(v)) pc.push_back(v);
    }
    for (int v: pc) if (v == M_) return true;
    return false;
}

#endif // ALGS4_NFA_HPP
