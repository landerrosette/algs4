#ifndef ALGS4_KOSARAJUSCC_H
#define ALGS4_KOSARAJUSCC_H


#include "Digraph.h"
#include "CC.h"
#include "DepthFirstOrder.h"

class KosarajuSCC : private CC {
public:
    KosarajuSCC(const Digraph &G);

    bool stronglyConnected(int v, int w) const { return connected(v, w); }

    using CC::getId, CC::getCount;
};


#endif //ALGS4_KOSARAJUSCC_H
