#include "Digraph.h"

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
