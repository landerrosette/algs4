#include "EdgeWeightedDigraph.h"

algs4::EdgeWeightedDigraph::EdgeWeightedDigraph(std::istream &in) : GraphBase(in) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(DirectedEdge(v, w, weight));
    }
}

void algs4::EdgeWeightedDigraph::addEdge(const DirectedEdge &e) {
    adj_[e.from()].push_front(e);
    ++E_;
}

std::list<algs4::DirectedEdge> algs4::EdgeWeightedDigraph::edges() const {
    std::list<DirectedEdge> bag;
    for (int v = 0; v < V_; ++v) {
        for (const auto &e: adj_[v])
            bag.push_front(e);
    }
    return bag;
}
