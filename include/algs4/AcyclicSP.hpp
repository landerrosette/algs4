#ifndef ALGS4_ACYCLICSP_H
#define ALGS4_ACYCLICSP_H


#include "SP.h"
#include "Topological.h"

namespace algs4 {
    class AcyclicSP : public SP {
    public:
        AcyclicSP(const EdgeWeightedDigraph &G, int s);
    };
}

inline algs4::AcyclicSP::AcyclicSP(const EdgeWeightedDigraph &G, int s) : SP(G, s) {
    Topological top(G);
    for (int v: top.order())
        relax(G, v);
}


#endif //ALGS4_ACYCLICSP_H
