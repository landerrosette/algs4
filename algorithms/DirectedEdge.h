#ifndef ALGS4_DIRECTEDEDGE_H
#define ALGS4_DIRECTEDEDGE_H


#include <iomanip>
#include <iostream>

#include "Edge.h"

class DirectedEdge : private Edge {
public:
    using Edge::Edge, Edge::weight;

    int from() const { return v; }

    int to() const { return w; }

    friend std::ostream &operator<<(std::ostream &os, const DirectedEdge &e) {
        return os << e.v << "->" << e.w << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
    }
};


#endif //ALGS4_DIRECTEDEDGE_H
