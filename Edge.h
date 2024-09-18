#ifndef ALGS4_EDGE_H
#define ALGS4_EDGE_H


#include <iostream>
#include <memory>

class Edge {
private:
    struct Edge_ {
        const int v, w;      // 顶点
        const double weight; // 边的权重

        Edge_(int v, int w, double weight) : v(v), w(w), weight(weight) {}
    };

    std::shared_ptr<Edge_> e;

public:
    Edge() = default;

    Edge(int v, int w, double weight) : e(std::make_shared<Edge_>(v, w, weight)) {}

    double weight() const { return e->weight; }

    int either() const { return e->v; }

    int other(int vertex) const;
};

inline bool operator<(const Edge& l, const Edge& r) { return l.weight() < r.weight(); }

inline bool operator>(const Edge& l, const Edge& r) { return l.weight() > r.weight(); }

std::ostream& operator<<(std::ostream& os, const Edge& e);

std::ostream& operator<<(std::ostream& os, const Edge* e);


#endif //ALGS4_EDGE_H
