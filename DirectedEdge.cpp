#include "DirectedEdge.h"
#include <iomanip>

std::ostream &operator<<(std::ostream &os, const DirectedEdge &e) {
    return os << e.edge_->v << "->" << e.edge_->w << " " << std::fixed << std::setprecision(2) << e.edge_->weight <<
           " ";
}
