#include "DirectedEdge.h"

#include <iomanip>

std::ostream &algs4::operator<<(std::ostream &os, const DirectedEdge &e) {
    return os << e.v << "->" << e.w << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
}