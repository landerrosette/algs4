#include "EdgeWeightedGraph.h"

EdgeWeightedGraph::EdgeWeightedGraph(std::istream&& in) : EdgeWeightedGraph([&in]() {
    int i;
    return in >> i, i;
}()) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        addEdge(Edge(v, w, weight));
    }
}

void EdgeWeightedGraph::addEdge(const Edge& e) {
    int v = e.either(), w = e.other(v);
    adj_[v].push_front(e);
    adj_[w].push_front(e);
    ++E_;
}

std::forward_list<Edge> EdgeWeightedGraph::edges() const {
    std::forward_list<Edge> bag;
    for (int v = 0; v < V_; ++v) {
        for (const auto& e : adj_[v]) {
            if (e.other(v) > v) bag.push_front(e);
        }
    }
    return bag;
}
