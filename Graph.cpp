#include "Graph.h"

Graph::Graph(std::istream &in) : Graph(readInt(in)) {
    int E = readInt(in);
    for (int i = 0; i < E; ++i) {
        int v = readInt(in);
        int w = readInt(in);
        addEdge(v, w);
    }
}

void Graph::addEdge(int v, int w) {
    adj[v].push_front(w);
    adj[w].push_front(v);
    ++E;
}

int Graph::readInt(std::istream &in) {
    int i;
    in >> i;
    return i;
}

std::ostream &operator<<(std::ostream &os, const Graph &G) {
    os << G.V << " vertices, " << G.E << " edges" << "\n";
    for (int v = 0; v < G.V; ++v) {
        os << v << ": ";
        for (int w: G.adj[v]) os << w << " ";
        os << "\n";
    }
    return os;
}
