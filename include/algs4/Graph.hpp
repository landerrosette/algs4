#ifndef ALGS4_GRAPH_HPP
#define ALGS4_GRAPH_HPP


#include <cassert>
#include <cstddef>

#include "GraphBase.hpp"

namespace algs4 {
    class Graph : public GraphBase<int> {
    public:
        explicit Graph(int V) : GraphBase(V) {}
        explicit Graph(std::istream &in);

        void addEdge(int v, int w);
    };
}

inline algs4::Graph::Graph(std::istream &in) : GraphBase(in) {
    std::ptrdiff_t E;
    in >> E;
    assert(E >= 0);
    for (decltype(E) i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

inline void algs4::Graph::addEdge(int v, int w) {
    assert(v >= 0 && v < V_);
    assert(w >= 0 && w < V_);
    adj_[v].push_back(w);
    adj_[w].push_back(v);
    ++E_;
}


#endif //ALGS4_GRAPH_HPP
