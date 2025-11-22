#ifndef ALGS4_EDGEWEIGHTEDGRAPH_H
#define ALGS4_EDGEWEIGHTEDGRAPH_H


#include <iostream>
#include <list>

#include "Edge.h"
#include "GraphBase.h"

namespace algs4 {
    class EdgeWeightedGraph : public GraphBase<Edge> {
    public:
        explicit EdgeWeightedGraph(int V) : GraphBase(V) {}
        explicit EdgeWeightedGraph(std::istream &in);

        void addEdge(const Edge &e);
        std::list<Edge> edges() const;
    };
}


#endif //ALGS4_EDGEWEIGHTEDGRAPH_H