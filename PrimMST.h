#ifndef ALGS4_PRIMMST_H
#define ALGS4_PRIMMST_H


#include "MST.h"
#include "EdgeWeightedGraph.h"
#include <vector>
#include "IndexMinPQ.h"

class PrimMST : public MST {
private:
    std::vector<Edge> edgeTo;   // 距离树最近的边
    std::vector<double> distTo; // distTo[w] = edgeTo[w].weight()
    std::vector<bool> marked;   // 如果v在树中则为true
    IndexMinPQ<double> pq;      // 有效的横切边

    void visit(const EdgeWeightedGraph &G, int v);

public:
    explicit PrimMST(const EdgeWeightedGraph &G);

    std::list<Edge> edges() const override;
};


#endif //ALGS4_PRIMMST_H
