#ifndef ALGS4_ACYCLICSP_HPP
#define ALGS4_ACYCLICSP_HPP


#include "SP.hpp"
#include "Topological.hpp"

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


#endif //ALGS4_ACYCLICSP_HPP
