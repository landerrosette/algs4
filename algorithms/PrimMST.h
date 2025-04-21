#ifndef ALGS4_PRIMMST_H
#define ALGS4_PRIMMST_H


#include <optional>
#include <vector>

#include "EdgeWeightedGraph.h"
#include "IndexMinPQ.h"
#include "MST.h"

class PrimMST : public MST {
private:
    std::vector<std::optional<Edge> > edgeTo; // shortest edge from tree vertex
    std::vector<double> distTo;               // distTo[w] = edgeTo[w].weight()
    std::vector<bool> marked;                 // true if v on tree
    IndexMinPQ<double> pq;                    // eligible crossing edges

    void visit(const EdgeWeightedGraph &G, int v);

public:
    explicit PrimMST(const EdgeWeightedGraph &G);

    std::list<Edge> edges() const override;
};


#endif //ALGS4_PRIMMST_H
