#ifndef ALGS4_DIGRAPH_HPP
#define ALGS4_DIGRAPH_HPP


#include <cassert>
#include <cstddef>

#include "GraphBase.hpp"

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
    std::ptrdiff_t E;
    in >> E;
    assert(E >= 0);
    for (decltype(E) i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

inline void algs4::Digraph::addEdge(int v, int w) {
    assert(v >= 0 && v < V_);
    assert(w >= 0 && w < V_);
    adj_[v].push_back(w);
    ++E_;
}

inline algs4::Digraph algs4::Digraph::reverse() const {
    Digraph R(V_);
    for (int v = 0; v < V_; ++v)
        for (int w: adj(v))
            R.addEdge(w, v);
    return R;
}


#endif //ALGS4_DIGRAPH_HPP
