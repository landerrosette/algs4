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

        constexpr SP(const EdgeWeightedDigraph &G, int s);
        constexpr SP(const SP &) = default;
        constexpr SP &operator=(const SP &) = default;
        constexpr SP(SP &&) noexcept = default;
        constexpr SP &operator=(SP &&) noexcept = default;

        constexpr void relax(const EdgeWeightedDigraph &G, int v);
        virtual constexpr void onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {}
        virtual constexpr void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {}

    public:
        virtual constexpr ~SP() = default;

        constexpr double distTo(int v) const;
        constexpr bool hasPathTo(int v) const;
        constexpr std::vector<DirectedEdge> pathTo(int v) const;
    };
}

constexpr void algs4::SP::relax(const EdgeWeightedDigraph &G, int v) {
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

constexpr algs4::SP::SP(const EdgeWeightedDigraph &G, int s)
    : edgeTo(G.V()), distTo_(G.V(), std::numeric_limits<double>::infinity()) {
    assert(s >= 0 && s < std::ssize(distTo_));
    distTo_[s] = 0.0;
}

constexpr double algs4::SP::distTo(int v) const {
    assert(v >= 0 && v < std::ssize(distTo_));
    return distTo_[v];
}

constexpr bool algs4::SP::hasPathTo(int v) const {
    assert(v >= 0 && v < std::ssize(distTo_));
    return distTo_[v] < std::numeric_limits<double>::infinity();
}

constexpr std::vector<algs4::DirectedEdge> algs4::SP::pathTo(int v) const {
    assert(v >= 0 && v < std::ssize(distTo_));
    std::vector<DirectedEdge> path;
    for (auto e = edgeTo[v]; e; e = edgeTo[e.from()])
        path.push_back(e);
    std::ranges::reverse(path);
    return path;
}


#endif //ALGS4_SP_HPP
