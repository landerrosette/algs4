#include "Digraph.h"

Digraph::Digraph(std::istream &in) : Digraph([](std::istream &in) -> int {
    int i;
    in >> i;
    return i;
}(in)) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
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
