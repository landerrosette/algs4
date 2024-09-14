#ifndef ALGS4_EDGE_H
#define ALGS4_EDGE_H


#include <iostream>

class Edge {
private:
    const int v, w;          // 顶点
    const double weight_;    // 边的权重

public:
    Edge(int v, int w, double weight) : v(v), w(w), weight_(weight) {}

    double weight() const { return weight_; }

    int either() const { return v; }

    int other(int vertex) const;
};

inline bool operator<(const Edge &l, const Edge &r) { return l.weight() < r.weight(); }

inline bool operator>(const Edge &l, const Edge &r) { return l.weight() > r.weight(); }

std::ostream &operator<<(std::ostream &os, const Edge &e);


#endif //ALGS4_EDGE_H
