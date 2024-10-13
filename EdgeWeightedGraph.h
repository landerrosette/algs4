#ifndef ALGS4_EDGEWEIGHTEDGRAPH_H
#define ALGS4_EDGEWEIGHTEDGRAPH_H


#include "GraphBase.h"
#include "Edge.h"
#include <iostream>
#include <list>

class EdgeWeightedGraph : public GraphBase<Edge> {
public:
    EdgeWeightedGraph(int V) : GraphBase(V) {
    }

    EdgeWeightedGraph(std::istream &&in);

    void addEdge(const Edge &e);

    std::list<Edge> edges() const;
};


#endif //ALGS4_EDGEWEIGHTEDGRAPH_H
