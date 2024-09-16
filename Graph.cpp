#include "Graph.h"

Graph::Graph(std::istream &&in) : Graph([&in]() {
    int i;
    return in >> i, i;
}()) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

void Graph::addEdge(int v, int w) {
    adj_[v].push_front(w);
    adj_[w].push_front(v);
    ++E_;
}
