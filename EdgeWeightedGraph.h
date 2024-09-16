#ifndef ALGS4_EDGEWEIGHTEDGRAPH_H
#define ALGS4_EDGEWEIGHTEDGRAPH_H


#include "GraphBase.h"
#include "Edge.h"
#include <iostream>
#include <forward_list>
#include <memory>

class EdgeWeightedGraph : public GraphBase<std::shared_ptr<Edge>> {
public:
    EdgeWeightedGraph(int V) : GraphBase(V) {}

    EdgeWeightedGraph(std::istream&& in);

    void addEdge(const std::shared_ptr<Edge>& e);

    std::forward_list<Edge> edges() const;
};


#endif //ALGS4_EDGEWEIGHTEDGRAPH_H
