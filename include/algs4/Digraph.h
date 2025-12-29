#ifndef ALGS4_DIGRAPH_H
#define ALGS4_DIGRAPH_H


#include <iostream>

#include "GraphBase.h"

namespace algs4 {
    class Digraph : public GraphBase<int> {
    public:
        explicit Digraph(int V) : GraphBase(V) {}
        explicit Digraph(std::istream &in);

        void addEdge(int v, int w);
        Digraph reverse() const;
    };
}

inline algs4::Digraph::Digraph(std::istream &in) : GraphBase(in) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

inline void algs4::Digraph::addEdge(int v, int w) {
    adj_[v].push_front(w);
    ++E_;
}

inline algs4::Digraph algs4::Digraph::reverse() const {
    Digraph R(V_);
    for (int v = 0; v < V_; ++v)
        for (int w: adj(v))
            R.addEdge(w, v);
    return R;
}


#endif //ALGS4_DIGRAPH_H
