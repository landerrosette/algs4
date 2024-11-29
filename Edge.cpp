#include "Edge.h"
#include <stdexcept>

int Edge::other(int vertex) const {
    if (vertex == edge_->v) return edge_->w;
    else if (vertex == edge_->w) return edge_->v;
    else throw std::runtime_error("Inconsistent edge");
}
