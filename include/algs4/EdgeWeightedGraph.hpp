#ifndef ALGS4_EDGEWEIGHTEDGRAPH_HPP
#define ALGS4_EDGEWEIGHTEDGRAPH_HPP


#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

#include "Edge.hpp"
#include "GraphBase.hpp"

namespace algs4 {
    class EdgeWeightedGraph : public GraphBase<Edge> {
    public:
        explicit EdgeWeightedGraph(int V) : GraphBase(V) {}
        explicit EdgeWeightedGraph(std::istream &in);

        void addEdge(const Edge &e);
        std::vector<Edge> edges() const;
    };
}

inline algs4::EdgeWeightedGraph::EdgeWeightedGraph(std::istream &in) : GraphBase(in) {
    std::ptrdiff_t E;
    in >> E;
    assert(E >= 0);
    for (decltype(E) i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(Edge(v, w, weight));
    }
}

inline void algs4::EdgeWeightedGraph::addEdge(const Edge &e) {
    int v = e.either(), w = e.other(v);
    adj_[v].push_back(e);
    adj_[w].push_back(e);
    ++E_;
}

inline std::vector<algs4::Edge> algs4::EdgeWeightedGraph::edges() const {
    std::vector<Edge> bag;
    for (int v = 0; v < V_; ++v)
        for (const auto &e: adj(v))
            if (e.other(v) > v)
                bag.push_back(e);
    std::ranges::reverse(bag);
    return bag;
}


#endif //ALGS4_EDGEWEIGHTEDGRAPH_HPP
