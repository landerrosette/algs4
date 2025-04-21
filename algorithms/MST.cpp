#include "MST.h"

double MST::weight() const {
    double weight = 0.0;
    for (const auto &e: edges()) weight += e.weight();
    return weight;
}
