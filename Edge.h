#ifndef ALGS4_EDGE_H
#define ALGS4_EDGE_H


#include <iostream>
#include <iomanip>

class Edge {
protected:
    int v, w;
    double weight_;

public:
    Edge(int v, int w, double weight) : v(v), w(w), weight_(weight) {}

    double weight() const { return weight_; }

    int either() const { return v; }

    int other(int vertex) const;

    friend std::ostream &operator<<(std::ostream &os, const Edge &e) {
        return os << e.v << "-" << e.w << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
    }
};

inline bool operator<(const Edge &l, const Edge &r) { return l.weight() < r.weight(); }

inline bool operator>(const Edge &l, const Edge &r) { return r < l; }


#endif //ALGS4_EDGE_H
