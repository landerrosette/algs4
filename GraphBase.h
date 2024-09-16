#ifndef ALGS4_GRAPHBASE_H
#define ALGS4_GRAPHBASE_H


#include <forward_list>
#include <vector>
#include <iostream>

template <typename T>
class GraphBase {
protected:
    const int V_;                           // 顶点数目
    int E_;                                 // 边的数目
    std::vector<std::forward_list<T>> adj_; // 邻接表

public:
    GraphBase(int V) : V_(V), E_(0), adj_(V) {}

    virtual ~GraphBase() = default;

    int V() const { return V_; }

    int E() const { return E_; }

    std::forward_list<T> adj(int v) const { return adj_[v]; }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const GraphBase<T>& G) {
    os << G.V() << " vertices, " << G.E() << " edges" << "\n";
    for (int v = 0; v < G.V(); ++v) {
        os << v << ": ";
        for (T w : G.adj(v)) os << w << " ";
        os << "\n";
    }
    return os;
}


#endif //ALGS4_GRAPHBASE_H
