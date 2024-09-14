#include "EdgeWeightedGraph.h"

EdgeWeightedGraph::EdgeWeightedGraph(std::istream &in) : EdgeWeightedGraph([](std::istream &in) -> int {
    int i;
    in >> i;
    return i;
}(in)) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(std::make_shared<Edge>(v, w, weight));
    }
}

void EdgeWeightedGraph::addEdge(const std::shared_ptr<Edge> &e) {
    int v = e->either(), w = e->other(v);
    adj_[v].push_front(e);
    adj_[w].push_front(e);
    ++E_;
}

std::forward_list<Edge> EdgeWeightedGraph::edges() const {
    std::forward_list<Edge> b;
    for (int v = 0; v < V_; ++v) {
        for (const auto &e: adj_[v]) {
            if (e->other(v) > v) b.push_front(*e);
        }
    }
    return b;
}
