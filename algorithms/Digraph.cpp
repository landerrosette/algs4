#include "Digraph.h"

algs4::Digraph::Digraph(std::istream &in) : GraphBase(in) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

void algs4::Digraph::addEdge(int v, int w) {
    adj_[v].push_front(w);
    ++E_;
}

algs4::Digraph algs4::Digraph::reverse() const {
    Digraph R(V_);
    for (int v = 0; v < V_; ++v)
        for (int w: adj(v))
            R.addEdge(w, v);
    return R;
}
