#ifndef KRUSKALMST_H
#define KRUSKALMST_H


#include "MST.h"
#include <deque>
#include "EdgeWeightedGraph.h"
#include "UF.h"
#include <forward_list>

class KruskalMST : public MST {
private:
    std::deque<Edge> mst;

public:
    KruskalMST(const EdgeWeightedGraph& G);

    std::forward_list<Edge> edges() const override;
};


#endif //KRUSKALMST_H
