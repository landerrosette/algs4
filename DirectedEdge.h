#ifndef DIRECTEDEDGE_H
#define DIRECTEDEDGE_H


#include "Edge.h"
#include <iostream>

class DirectedEdge : private Edge {
public:
    using Edge::Edge, Edge::weight;

    int from() const { return edge_->v; }

    int to() const { return edge_->w; }
};

std::ostream& operator<<(std::ostream& os, const DirectedEdge& e);


#endif //DIRECTEDEDGE_H
