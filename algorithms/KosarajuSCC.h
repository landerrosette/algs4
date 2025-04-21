#ifndef ALGS4_KOSARAJUSCC_H
#define ALGS4_KOSARAJUSCC_H


#include "CCBase.h"
#include "Digraph.h"

class KosarajuSCC : public CCBase {
public:
    explicit KosarajuSCC(const Digraph &G);

    bool stronglyConnected(int v, int w) const { return connected(v, w); }
};


#endif //ALGS4_KOSARAJUSCC_H
