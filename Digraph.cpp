#include "Digraph.h"

Digraph::Digraph(std::istream &in) : Digraph(readInt(in)) {
    int E = readInt(in);
    for (int i = 0; i < E; ++i) {
        int v = readInt(in);
        int w = readInt(in);
        addEdge(v, w);
    }
}

void Digraph::addEdge(int v, int w) {
    adj[v].push_front(w);
    ++E;
}

Digraph Digraph::reverse() const {
    Digraph R(V);
    for (int v = 0; v < V; ++v) {
        for (int w: getAdj(v)) R.addEdge(w, v);
    }
    return R;
}

std::ostream &operator<<(std::ostream &os, const Digraph &G) {
    os << static_cast<const Graph &>(G);
    return os;
}
