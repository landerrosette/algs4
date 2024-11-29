#ifndef DIRECTEDEDGE_H
#define DIRECTEDEDGE_H


#include "Edge.h"
#include <iostream>
#include <iomanip>

class DirectedEdge : private Edge {
public:
    using Edge::Edge, Edge::weight;

    int from() const { return edge_->v; }

    int to() const { return edge_->w; }

    using Edge::operator bool;

    friend std::ostream &operator<<(std::ostream &os, const DirectedEdge &e) {
        return os << e.edge_->v << "->" << e.edge_->w << " " << std::fixed << std::setprecision(2) << e.edge_->weight <<
               " ";
    }
};


#endif //DIRECTEDEDGE_H
