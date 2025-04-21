#include "NFA.h"

#include <algorithm>
#include <list>

#include "DirectedDFS.h"

NFA::NFA(std::string_view regexp) : re(regexp), M(re.length()), G(M + 1) {
    std::list<int> ops;
    for (int i = 0; i < M; ++i) {
        int lp = i; // left position
        if (re[i] == '(' || re[i] == '|') ops.push_front(i);
        else if (re[i] == ')') {
            int orPos = ops.front();
            ops.pop_front();
            if (re[orPos] == '|') {
                lp = ops.front();
                ops.pop_front();
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

bool NFA::recognizes(std::string_view txt) const {
    std::list<int> pc;
    DirectedDFS dfs(G, 0);
    for (int v = 0; v < G.V(); ++v)
        if (dfs.marked(v)) pc.push_front(v);

    // Compute possible NFA states for txt[i+1].
    for (int i = 0; i < txt.length(); ++i) {
        std::list<int> match;
        for (int v: pc) {
            if (v < M)
                if (re[v] == txt[i] || re[v] == '.') match.push_front(v + 1);
        }
        pc = std::list<int>();
        dfs = DirectedDFS(G, match);
        for (int v = 0; v < G.V(); ++v)
            if (dfs.marked(v)) pc.push_front(v);
    }
    // for (int v: pc)
    //     if (v == M) return true;
    if (std::any_of(pc.begin(), pc.end(), [this](int v) { return v == M; })) return true;
    return false;
}
