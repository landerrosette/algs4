#ifndef ALGS4_DEPTHFIRSTPATHS_HPP
#define ALGS4_DEPTHFIRSTPATHS_HPP


#include "Paths.hpp"

namespace algs4 {
    class DepthFirstPaths : public Paths {
    private:
        constexpr void dfs(const Graph &G, int v);

    public:
        constexpr DepthFirstPaths(const Graph &G, int s) : Paths(G, s) { dfs(G, s); }
    };
}

constexpr void algs4::DepthFirstPaths::dfs(const Graph &G, int v) {
    marked_[v] = true;
    for (int w: G.adj(v)) {
        if (!marked_[w]) {
            edgeTo_[w] = v;
            dfs(G, w);
        }
    }
}


#endif //ALGS4_DEPTHFIRSTPATHS_HPP
