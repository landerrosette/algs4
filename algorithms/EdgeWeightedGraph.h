#ifndef ALGS4_EDGEWEIGHTEDGRAPH_H
#define ALGS4_EDGEWEIGHTEDGRAPH_H


#include <iostream>
#include <list>

#include "Edge.h"
#include "GraphBase.h"

namespace algs4 {
    class EdgeWeightedGraph : public GraphBase<Edge> {
    public:
        explicit EdgeWeightedGraph(int V) : GraphBase(V) {}
        explicit EdgeWeightedGraph(std::istream &in);

        void addEdge(const Edge &e);
        std::list<Edge> edges() const;
    };
}

inline algs4::EdgeWeightedGraph::EdgeWeightedGraph(std::istream &in) : GraphBase(in) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(Edge(v, w, weight));
    }
}

inline void algs4::EdgeWeightedGraph::addEdge(const Edge &e) {
    int v = e.either(), w = e.other(v);
    adj_[v].push_front(e);
    adj_[w].push_front(e);
    ++E_;
}

inline std::list<algs4::Edge> algs4::EdgeWeightedGraph::edges() const {
    std::list<Edge> bag;
    for (int v = 0; v < V_; ++v)
        for (const auto &e: adj_[v])
            if (e.other(v) > v)
                bag.push_front(e);
    return bag;
}


#endif //ALGS4_EDGEWEIGHTEDGRAPH_H
