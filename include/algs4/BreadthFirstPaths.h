#ifndef ALGS4_BREADTHFIRSTPATHS_H
#define ALGS4_BREADTHFIRSTPATHS_H


#include <queue>

#include "Paths.h"

namespace algs4 {
    class BreadthFirstPaths : public Paths {
    private:
        void bfs(const Graph &G, int s);

    public:
        BreadthFirstPaths(const Graph &G, int s) : Paths(G, s) { bfs(G, s); }
    };
}

inline void algs4::BreadthFirstPaths::bfs(const Graph &G, int s) {
    std::queue<int> queue;
    marked[s] = true;
    queue.push(s);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int w: G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                marked[w] = true;
                queue.push(w);
            }
        }
    }
}


#endif //ALGS4_BREADTHFIRSTPATHS_H
