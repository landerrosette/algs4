#ifndef ALGS4_BREADTHFIRSTPATHS_H
#define ALGS4_BREADTHFIRSTPATHS_H


#include "Paths.h"

namespace algs4 {
    class BreadthFirstPaths : public Paths {
    private:
        void bfs(const Graph &G, int s);

    public:
        BreadthFirstPaths(const Graph &G, int s) : Paths(G, s) { bfs(G, s); }
    };
}


#endif //ALGS4_BREADTHFIRSTPATHS_H
