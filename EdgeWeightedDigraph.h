#ifndef EDGEWEIGHTEDDIGRAPH_H
#define EDGEWEIGHTEDDIGRAPH_H


#include "GraphBase.h"
#include "DirectedEdge.h"
#include <iostream>
#include <forward_list>

class EdgeWeightedDigraph : public GraphBase<DirectedEdge> {
public:
    EdgeWeightedDigraph(int V) : GraphBase(V) {}

    EdgeWeightedDigraph(std::istream&& in);

    void addEdge(const DirectedEdge& e);

    std::forward_list<DirectedEdge> edges() const;
};


#endif //EDGEWEIGHTEDDIGRAPH_H
