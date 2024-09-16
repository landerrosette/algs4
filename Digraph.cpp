#include "Digraph.h"

Digraph::Digraph(std::istream&& in) : Digraph([&in]() {
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

void Digraph::addEdge(int v, int w) {
    adj_[v].push_front(w);
    ++E_;
}

Digraph Digraph::reverse() const {
    Digraph R(V_);
    for (int v = 0; v < V_; ++v) {
        for (int w : adj(v)) R.addEdge(w, v);
    }
    return R;
}
