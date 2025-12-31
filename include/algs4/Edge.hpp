#ifndef ALGS4_EDGE_H
#define ALGS4_EDGE_H


#include <cassert>
#include <compare>
#include <iomanip>
#include <iostream>

#include "EdgeBase.h"

namespace algs4 {
    class Edge : public EdgeBase {
        friend std::ostream &operator<<(std::ostream &os, const Edge &e);

    public:
        Edge(int v, int w, double weight) : EdgeBase(v, w, weight) {}

        int either() const { return v; }
        int other(int vertex) const;
    };

    inline auto operator<=>(const Edge &l, const Edge &r) { return l.weight() <=> r.weight(); }
    inline bool operator==(const Edge &l, const Edge &r) { return l.weight() == r.weight(); }
    std::ostream &operator<<(std::ostream &os, const Edge &e);
}

inline int algs4::Edge::other(int vertex) const {
    if (vertex == v) return w;
    else if (vertex == w) return v;
    else
        assert(false);
}

inline std::ostream &algs4::operator<<(std::ostream &os, const Edge &e) {
    return os << e.v << "-" << e.w << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
}


#endif //ALGS4_EDGE_H
