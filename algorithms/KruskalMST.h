#ifndef ALGS4_KRUSKALMST_H
#define ALGS4_KRUSKALMST_H


#include <list>

#include "EdgeWeightedGraph.h"
#include "MST.h"

class KruskalMST : public MST {
private:
    std::list<Edge> mst;

public:
    explicit KruskalMST(const EdgeWeightedGraph &G);

    std::list<Edge> edges() const override { return mst; }
};


#endif //ALGS4_KRUSKALMST_H
