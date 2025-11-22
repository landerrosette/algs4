#include "AcyclicSP.h"

#include "Topological.h"

algs4::AcyclicSP::AcyclicSP(const EdgeWeightedDigraph &G, int s) : SP(G, s) {
    Topological top(G);
    for (int v: top.order())
        relax(G, v);
}
