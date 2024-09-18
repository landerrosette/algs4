#include "SP.h"

void SP::relax(const EdgeWeightedDigraph& G, int v) {
    for (const auto& e : G.adj(v)) {
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight()) {
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo[w] = e;
        }
    }
}

SP::SP(const EdgeWeightedDigraph& G, int s) : edgeTo(G.V()), distTo_(G.V(), std::numeric_limits<double>::infinity()) {
    distTo_[s] = 0.0;
}

std::list<DirectedEdge> SP::pathTo(int v) const {
    std::list<DirectedEdge> path;
    for (auto e = edgeTo[v]; e; e = edgeTo[e.from()]) path.push_front(e);
    return path;
}
