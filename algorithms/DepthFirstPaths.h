#ifndef ALGS4_DEPTHFIRSTPATHS_H
#define ALGS4_DEPTHFIRSTPATHS_H


#include "Paths.h"

namespace algs4 {
    class DepthFirstPaths : public Paths {
    private:
        void dfs(const Graph &G, int v);

    public:
        DepthFirstPaths(const Graph &G, int s) : Paths(G, s) { dfs(G, s); }
    };
}

inline void algs4::DepthFirstPaths::dfs(const Graph &G, int v) {
    marked[v] = true;
    for (int w: G.adj(v)) {
        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}


#endif //ALGS4_DEPTHFIRSTPATHS_H
