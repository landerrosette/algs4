#ifndef EDGEWEIGHTEDDIGRAPH_H
#define EDGEWEIGHTEDDIGRAPH_H


#include <iostream>
#include <list>

#include "DirectedEdge.h"
#include "GraphBase.h"

class EdgeWeightedDigraph : public GraphBase<DirectedEdge> {
public:
    explicit EdgeWeightedDigraph(int V) : GraphBase(V) {}

    explicit EdgeWeightedDigraph(std::istream &in);

    void addEdge(const DirectedEdge &e);

    std::list<DirectedEdge> edges() const;
};


#endif //EDGEWEIGHTEDDIGRAPH_H
