#ifndef ALGS4_GRAPHBASE_H
#define ALGS4_GRAPHBASE_H


#include <forward_list>
#include <vector>
#include <iostream>

template<typename T>
class GraphBase;

template<typename T>
std::ostream &operator<<(std::ostream &os, const GraphBase<T> &G);

template<typename T>
class GraphBase {
protected:
    const int V;                                // 顶点数目
    int E;                                      // 边的数目
    std::vector<std::forward_list<T>> adj;      // 邻接表

public:
    GraphBase(int V) : V(V), E(0), adj(V) {}

    virtual ~GraphBase() = default;

    int getV() const { return V; }

    int getE() const { return E; }

    std::forward_list<T> getAdj(int v) const { return adj[v]; }

    friend std::ostream &operator<<<>(std::ostream &os, const GraphBase &G);
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const GraphBase<T> &G) {
    os << G.V << " vertices, " << G.E << " edges" << "\n";
    for (int v = 0; v < G.V; ++v) {
        os << v << ": ";
        for (T w: G.adj[v]) os << w << " ";
        os << "\n";
    }
    return os;
}


#endif //ALGS4_GRAPHBASE_H
