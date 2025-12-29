#ifndef ALGS4_GRAPHBASE_H
#define ALGS4_GRAPHBASE_H


#include <iostream>
#include <list>
#include <vector>

namespace algs4 {
    template<typename T>
    class GraphBase {
    protected:
        const int V_;                    // number of vertices
        int E_;                          // number of edges
        std::vector<std::list<T> > adj_; // adjacency lists

        explicit GraphBase(int V) : V_(V), E_(0), adj_(V) {}
        explicit GraphBase(std::istream &in);
        ~GraphBase() = default;

    public:
        int V() const { return V_; }
        int E() const { return E_; }
        std::list<T> adj(int v) const { return adj_[v]; }
    };
}

template<typename T>
algs4::GraphBase<T>::GraphBase(std::istream &in) : GraphBase([&in] {
    int i;
    return in >> i, i;
}()) {}

template<typename T>
std::ostream &operator<<(std::ostream &os, const algs4::GraphBase<T> &G) {
    os << G.V() << " vertices, " << G.E() << " edges" << std::endl;
    for (int v = 0; v < G.V(); ++v) {
        os << v << ": ";
        for (T w: G.adj(v)) os << w << " ";
        os << std::endl;
    }
    return os;
}


#endif //ALGS4_GRAPHBASE_H
