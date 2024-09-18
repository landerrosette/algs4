#include "Edge.h"
#include <stdexcept>
#include <iomanip>

int Edge::other(int vertex) const {
    if (vertex == edge_->v) return edge_->w;
    else if (vertex == edge_->w) return edge_->v;
    else throw std::runtime_error("Inconsistent edge");
}

bool operator<(const Edge& l, const Edge& r) { return l.weight() < r.weight(); }

bool operator>(const Edge& l, const Edge& r) { return l.weight() > r.weight(); }

std::ostream& operator<<(std::ostream& os, const Edge& e) {
    int v = e.either();
    return os << v << "-" << e.other(v) << " " << std::fixed << std::setprecision(2) << e.weight() << " ";
}
