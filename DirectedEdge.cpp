#include "DirectedEdge.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const DirectedEdge& e) {
    return os << e.from() << "->" << e.to() << " " << std::fixed << std::setprecision(2) << e.weight() << " ";
}
