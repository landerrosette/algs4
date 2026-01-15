#ifndef ALGS4_DIRECTEDDFS_HPP
#define ALGS4_DIRECTEDDFS_HPP


#include <cassert>
#include <vector>

#include "Digraph.hpp"

namespace algs4 {
    class DirectedDFS {
    private:
        std::vector<bool> marked_;

        constexpr void dfs(const Digraph &G, int v);

    public:
        constexpr DirectedDFS(const Digraph &G, int s);
        constexpr DirectedDFS(const Digraph &G, const std::vector<int> &sources);

        constexpr bool marked(int v) const { return marked_[v]; }
    };
}

constexpr void algs4::DirectedDFS::dfs(const Digraph &G, int v) {
    marked_[v] = true;
    for (int w: G.adj(v))
        if (!marked_[w])
            dfs(G, w);
}

constexpr algs4::DirectedDFS::DirectedDFS(const Digraph &G, int s) : marked_(G.V()) {
    assert(s >= 0 && s < std::ssize(marked_));
    dfs(G, s);
}

constexpr algs4::DirectedDFS::DirectedDFS(const Digraph &G, const std::vector<int> &sources) : marked_(G.V()) {
    assert(!sources.empty());
    for (int s: sources) {
        assert(s >= 0 && s < std::ssize(marked_));
        if (!marked_[s])
            dfs(G, s);
    }
}


#endif //ALGS4_DIRECTEDDFS_HPP
