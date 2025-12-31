#ifndef ALGS4_PATHS_HPP
#define ALGS4_PATHS_HPP


#include <cassert>
#include <list>
#include <vector>

#include "Graph.hpp"

namespace algs4 {
    class Paths {
    protected:
        std::vector<bool> marked; // Has dfs() been called for this vertex?
        std::vector<int> edgeTo;  // last vertex on known path for this vertex
        const int s;              // source

    public:
        Paths(const Graph &G, int s) : marked(G.V()), edgeTo(G.V()), s(s) { assert(s >= 0 && s < marked.size()); }
        virtual ~Paths() = default;

        bool hasPathTo(int v) const { return marked[v]; }
        std::list<int> pathTo(int v) const;
    };
}

inline std::list<int> algs4::Paths::pathTo(int v) const {
    assert(v >= 0 && v < marked.size());
    std::list<int> path;
    for (int x = v; x != s; x = edgeTo[x])
        path.push_front(x);
    path.push_front(s);
    return path;
}


#endif //ALGS4_PATHS_HPP
