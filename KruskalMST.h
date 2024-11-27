#ifndef KRUSKALMST_H
#define KRUSKALMST_H


#include "MST.h"
#include <list>
#include "EdgeWeightedGraph.h"

class KruskalMST : public MST {
private:
    std::list<Edge> mst;

public:
    explicit KruskalMST(const EdgeWeightedGraph &G);

    std::list<Edge> edges() const override { return mst; }
};


#endif //KRUSKALMST_H
