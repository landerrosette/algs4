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
        addEdge(Edge(v, w, weight));
    }
}

void EdgeWeightedGraph::addEdge(const Edge &e) {
    int v = e.either(), w = e.other(v);
    adj[v].push_front(e);
    adj[w].push_front(e);
    ++E;
}

std::forward_list<Edge> EdgeWeightedGraph::edges() {
    std::forward_list<Edge> b;
    for (int v = 0; v < V; ++v) {
        for (Edge e: adj[v]) {
            if (e.other(v) > v) b.push_front(e);
        }
    }
    return b;
}
