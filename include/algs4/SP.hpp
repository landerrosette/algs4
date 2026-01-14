#ifndef ALGS4_SP_HPP
#define ALGS4_SP_HPP


#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

#include "DirectedEdge.hpp"
#include "EdgeWeightedDigraph.hpp"

namespace algs4 {
    class SP {
    protected:
        std::vector<DirectedEdge> edgeTo;
        std::vector<double> distTo_;

        SP(const EdgeWeightedDigraph &G, int s);
        SP(const SP &) = default;
        SP &operator=(const SP &) = default;
        SP(SP &&) noexcept = default;
        SP &operator=(SP &&) noexcept = default;

        void relax(const EdgeWeightedDigraph &G, int v);
        virtual void onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {}
        virtual void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {}

    public:
        virtual ~SP() = default;

        double distTo(int v) const;
        bool hasPathTo(int v) const;
        std::vector<DirectedEdge> pathTo(int v) const;
    };
}

inline void algs4::SP::relax(const EdgeWeightedDigraph &G, int v) {
    for (const auto &e: G.adj(v)) {
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight()) {
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo[w] = e;
            onEdgeRelaxed(G, v, e, w);
        }
        afterRelaxation(G, v, e, w);
    }
}

inline algs4::SP::SP(const EdgeWeightedDigraph &G, int s)
    : edgeTo(G.V()), distTo_(G.V(), std::numeric_limits<double>::infinity()) {
    assert(s >= 0 && s < std::ssize(distTo_));
    distTo_[s] = 0.0;
}

inline double algs4::SP::distTo(int v) const {
    assert(v >= 0 && v < std::ssize(distTo_));
    return distTo_[v];
}

inline bool algs4::SP::hasPathTo(int v) const {
    assert(v >= 0 && v < std::ssize(distTo_));
    return distTo_[v] < std::numeric_limits<double>::infinity();
}

inline std::vector<algs4::DirectedEdge> algs4::SP::pathTo(int v) const {
    assert(v >= 0 && v < std::ssize(distTo_));
    std::vector<DirectedEdge> path;
    for (auto e = edgeTo[v]; e; e = edgeTo[e.from()])
        path.push_back(e);
    std::ranges::reverse(path);
    return path;
}


#endif //ALGS4_SP_HPP
