#include "Edge.h"

#include <iomanip>
#include <stdexcept>

int algs4::Edge::other(int vertex) const {
    if (vertex == v)
        return w;
    else if (vertex == w)
        return v;
    else
        throw std::runtime_error("Inconsistent edge");
}

std::ostream &algs4::operator<<(std::ostream &os, const Edge &e) {
    return os << e.v << "-" << e.w << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
}
