#ifndef ALGS4_EDGEWEIGHTEDDIGRAPH_HPP
#define ALGS4_EDGEWEIGHTEDDIGRAPH_HPP


#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

#include "DirectedEdge.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class EdgeWeightedDigraph : public GraphBase<DirectedEdge> {
    public:
        constexpr explicit EdgeWeightedDigraph(int V) : GraphBase(V) {}
        explicit EdgeWeightedDigraph(std::istream &in);

        constexpr void addEdge(const DirectedEdge &e);
        constexpr std::vector<DirectedEdge> edges() const;
    };
}

inline algs4::EdgeWeightedDigraph::EdgeWeightedDigraph(std::istream &in) : GraphBase(in) {
    std::ptrdiff_t E;
    in >> E;
    assert(E >= 0);
    for (decltype(E) i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(DirectedEdge(v, w, weight));
    }
}

constexpr void algs4::EdgeWeightedDigraph::addEdge(const DirectedEdge &e) {
    adj_[e.from()].push_back(e);
    ++E_;
}

constexpr std::vector<algs4::DirectedEdge> algs4::EdgeWeightedDigraph::edges() const {
    std::vector<DirectedEdge> bag;
    for (int v = 0; v < V_; ++v)
        for (const auto &e: adj(v))
            bag.push_back(e);
    std::ranges::reverse(bag);
    return bag;
}


#endif //ALGS4_EDGEWEIGHTEDDIGRAPH_HPP
