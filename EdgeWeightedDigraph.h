#ifndef EDGEWEIGHTEDDIGRAPH_H
#define EDGEWEIGHTEDDIGRAPH_H


#include "GraphBase.h"
#include "DirectedEdge.h"
#include <iostream>
#include <list>

class EdgeWeightedDigraph : public GraphBase<DirectedEdge> {
public:
    explicit EdgeWeightedDigraph(int V) : GraphBase(V) {}

    explicit EdgeWeightedDigraph(std::istream &in);

    void addEdge(const DirectedEdge &e);

    std::list<DirectedEdge> edges() const;
};


#endif //EDGEWEIGHTEDDIGRAPH_H
