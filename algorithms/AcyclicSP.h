#ifndef ALGS4_ACYCLICSP_H
#define ALGS4_ACYCLICSP_H


#include "SP.h"

namespace algs4 {
    class AcyclicSP : public SP {
    public:
        AcyclicSP(const EdgeWeightedDigraph &G, int s);
    };
}


#endif //ALGS4_ACYCLICSP_H
