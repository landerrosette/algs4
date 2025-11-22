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


#endif //ALGS4_DEPTHFIRSTPATHS_H