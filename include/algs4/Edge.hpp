#ifndef ALGS4_EDGE_HPP
#define ALGS4_EDGE_HPP


#include <cassert>
#include <iomanip>
#include <ostream>

#include "EdgeBase.hpp"

namespace algs4 {
    class Edge : public EdgeBase {
        friend std::ostream &operator<<(std::ostream &os, const Edge &e);

    public:
        constexpr Edge() = default;
        constexpr Edge(int v, int w, double weight) : EdgeBase(v, w, weight) {}

        constexpr int either() const { return v; }
        constexpr int other(int vertex) const;
    };

    std::ostream &operator<<(std::ostream &os, const Edge &e);
}

constexpr int algs4::Edge::other(int vertex) const {
    if (vertex == v) return w;
    else if (vertex == w) return v;
    else
        assert(false);
}

inline std::ostream &algs4::operator<<(std::ostream &os, const Edge &e) {
    return os << e.v << "-" << e.w << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
}


#endif //ALGS4_EDGE_HPP
