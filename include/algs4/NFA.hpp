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
        std::string re; // match transitions
        int M;          // number of states
        Digraph G;      // epsilon transitions

    public:
        explicit NFA(std::string regexp);

        bool recognizes(std::string_view txt) const;
    };
}

inline algs4::NFA::NFA(std::string regexp) : re(std::move(regexp)), M(static_cast<int>(std::ssize(re))), G(M + 1) {
    std::stack<int> ops;
    for (int i = 0; i < M; ++i) {
        int lp = i; // left position
        if (re[i] == '(' || re[i] == '|') ops.push(i);
        else if (re[i] == ')') {
            int orPos = ops.top();
            ops.pop();
            if (re[orPos] == '|') {
                lp = ops.top();
                ops.pop();
                G.addEdge(lp, orPos + 1);
                G.addEdge(orPos, i);
            } else lp = orPos;
        }
        if (i < M - 1 && re[i + 1] == '*') {
            G.addEdge(lp, i + 1);
            G.addEdge(i + 1, lp);
        } // lookahead
        if (re[i] == '(' || re[i] == '*' || re[i] == ')') G.addEdge(i, i + 1);
    }
}

inline bool algs4::NFA::recognizes(std::string_view txt) const {
    std::vector<int> pc;
    DirectedDFS dfs(G, 0);
    for (int v = 0; v < G.V(); ++v)
        if (dfs.marked(v)) pc.push_back(v);

    // Compute possible NFA states for txt[i+1].
    for (char c: txt) {
        std::vector<int> match;
        for (int v: pc)
            if (v < M)
                if (re[v] == c || re[v] == '.') match.push_back(v + 1);
        pc.clear();
        dfs = DirectedDFS(G, match);
        for (int v = 0; v < G.V(); ++v)
            if (dfs.marked(v)) pc.push_back(v);
    }
    for (int v: pc) if (v == M) return true;
    return false;
}


#endif //ALGS4_NFA_HPP
