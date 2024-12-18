#ifndef ALGS4_EDGE_H
#define ALGS4_EDGE_H


#include <iostream>
#include <memory>
#include <iomanip>

class Edge {
protected:
    struct Edge_ {
        const int v, w;      // 顶点
        const double weight; // 边的权重

        Edge_(int v, int w, double weight) : v(v), w(w), weight(weight) {}
    };

    std::shared_ptr<Edge_> edge_;

public:
    Edge() = default;

    Edge(int v, int w, double weight) : edge_(std::make_shared<Edge_>(v, w, weight)) {}

    double weight() const { return edge_->weight; }

    int either() const { return edge_->v; }

    int other(int vertex) const;

    explicit operator bool() const { return static_cast<bool>(edge_); }

    friend std::ostream &operator<<(std::ostream &os, const Edge &e) {
        return os << e.edge_->v << "-" << e.edge_->w << " " << std::fixed << std::setprecision(2) << e.edge_->weight <<
               " ";
    }
};

inline bool operator<(const Edge &l, const Edge &r) { return l.weight() < r.weight(); }

inline bool operator>(const Edge &l, const Edge &r) { return r < l; }


#endif //ALGS4_EDGE_H
