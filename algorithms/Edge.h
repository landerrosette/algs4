#ifndef ALGS4_EDGE_H
#define ALGS4_EDGE_H


#include <compare>
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


#endif //ALGS4_EDGE_H
