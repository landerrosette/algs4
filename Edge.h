#ifndef ALGS4_EDGE_H
#define ALGS4_EDGE_H


#include <iostream>

class Edge {
private:
    const int v;            // 顶点之一
    const int w;            // 另一个顶点
    const double weight;    // 边的权重

public:
    Edge(int v, int w, double weight) : v(v), w(w), weight(weight) {}

    double getWeight() const { return weight; }

    int either() const { return v; }

    int other(int vertex) const;

    friend bool operator<(const Edge &l, const Edge &r) { return l.weight < r.weight; }

    friend bool operator>(const Edge &l, const Edge &r) { return r < l; }

    friend std::ostream &operator<<(std::ostream &os, const Edge &e);
};


#endif //ALGS4_EDGE_H
