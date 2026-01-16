#ifndef ALGS4_BREADTHFIRSTPATHS_HPP
#define ALGS4_BREADTHFIRSTPATHS_HPP


#include <queue>

#include "Paths.hpp"

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
    marked_[s] = true;
    queue.push(s);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int w: G.adj(v)) {
            if (!marked_[w]) {
                edgeTo_[w] = v;
                marked_[w] = true;
                queue.push(w);
            }
        }
    }
}


#endif //ALGS4_BREADTHFIRSTPATHS_HPP
