#include "Graph.h"

algs4::Graph::Graph(std::istream &in) : GraphBase(in) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

void algs4::Graph::addEdge(int v, int w) {
    adj_[v].push_front(w);
    adj_[w].push_front(v);
    ++E_;
}
