#ifndef ALGS4_EDGEWEIGHTEDDIGRAPH_H
#define ALGS4_EDGEWEIGHTEDDIGRAPH_H


#include <iostream>
#include <list>

#include "DirectedEdge.h"
#include "GraphBase.h"

namespace algs4 {
    class EdgeWeightedDigraph : public GraphBase<DirectedEdge> {
    public:
        explicit EdgeWeightedDigraph(int V) : GraphBase(V) {}
        explicit EdgeWeightedDigraph(std::istream &in);

        void addEdge(const DirectedEdge &e);
        std::list<DirectedEdge> edges() const;
    };
}

inline algs4::EdgeWeightedDigraph::EdgeWeightedDigraph(std::istream &in) : GraphBase(in) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(DirectedEdge(v, w, weight));
    }
}

inline void algs4::EdgeWeightedDigraph::addEdge(const DirectedEdge &e) {
    adj_[e.from()].push_front(e);
    ++E_;
}

inline std::list<algs4::DirectedEdge> algs4::EdgeWeightedDigraph::edges() const {
    std::list<DirectedEdge> bag;
    for (int v = 0; v < V_; ++v)
        for (const auto &e: adj_[v])
            bag.push_front(e);
    return bag;
}


#endif //ALGS4_EDGEWEIGHTEDDIGRAPH_H
