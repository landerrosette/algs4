#ifndef KRUSKALMST_H
#define KRUSKALMST_H


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


#endif //KRUSKALMST_H
