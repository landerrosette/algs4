#include "Edge.h"
#include <stdexcept>
#include <iomanip>

int Edge::other(int vertex) const {
    if (vertex == e->v) return e->w;
    else if (vertex == e->w) return e->v;
    else throw std::runtime_error("Inconsistent edge");
}

std::ostream& operator<<(std::ostream& os, const Edge& e) {
    int v = e.either();
    os << v << "-" << e.other(v) << " " << std::fixed << std::setprecision(2) << e.weight() << " ";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Edge* e) {
    if (e) os << *e;
    return os;
}
