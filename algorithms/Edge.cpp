#include "Edge.h"

#include <stdexcept>

int Edge::other(int vertex) const {
    if (vertex == v) return w;
    else if (vertex == w) return v;
    else throw std::runtime_error("Inconsistent edge");
}
