#ifndef ALGS4_GRAPH_H
#define ALGS4_GRAPH_H


#include <cassert>
#include <iostream>

#include "GraphBase.h"

namespace algs4 {
    class Graph : public GraphBase<int> {
    public:
        explicit Graph(int V) : GraphBase(V) {}
        explicit Graph(std::istream &in);

        void addEdge(int v, int w);
    };
}

inline algs4::Graph::Graph(std::istream &in) : GraphBase(in) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

inline void algs4::Graph::addEdge(int v, int w) {
    assert(v >= 0 && v < V_);
    assert(w >= 0 && w < V_);
    adj_[v].push_front(w);
    adj_[w].push_front(v);
    ++E_;
}


#endif //ALGS4_GRAPH_H
