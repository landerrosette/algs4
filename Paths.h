#ifndef ALGS4_PATHS_H
#define ALGS4_PATHS_H


#include "Graph.h"
#include <vector>
#include <list>

class Paths {
protected:
    std::vector<bool> marked; // Has dfs() been called for this vertex?
    std::vector<int> edgeTo;  // last vertex on known path for this vertex
    const int s;              // source

public:
    Paths(const Graph &G, int s) : marked(G.V()), edgeTo(G.V()), s(s) {}

    virtual ~Paths() = default;

    bool hasPathTo(int v) const { return marked[v]; }

    std::list<int> pathTo(int v) const;
};


#endif //ALGS4_PATHS_H
