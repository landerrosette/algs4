#include "AcyclicSP.h"
#include "Topological.h"

AcyclicSP::AcyclicSP(const EdgeWeightedDigraph &G, int s) : SP(G, s) {
    Topological top(G);
    for (int v: top.order()) relax(G, v);
}
