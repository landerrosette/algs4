#ifndef ALGS4_EDGEWEIGHTEDDIGRAPH_H
#define ALGS4_EDGEWEIGHTEDDIGRAPH_H


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


#endif //ALGS4_EDGEWEIGHTEDDIGRAPH_H