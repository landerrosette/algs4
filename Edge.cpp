#include "Edge.h"
#include <stdexcept>
#include <iomanip>

int Edge::other(int vertex) const {
    if (vertex == v) return w;
    else if (vertex == w) return v;
    else throw std::runtime_error("Inconsistent edge");
}

std::ostream &operator<<(std::ostream &os, const Edge &e) {
    os << e.v << "-" << e.w << " " << std::fixed << std::setprecision(2) << e.weight << " ";
    return os;
}
