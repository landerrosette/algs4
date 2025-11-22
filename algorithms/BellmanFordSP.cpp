#include "BellmanFordSP.h"

#include "DirectedCycle.h"

void algs4::BellmanFordSP::onRelaxationSuccess(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (!onQ[w]) {
        queue.push_back(w);
        onQ[w] = true;
    }
}

void algs4::BellmanFordSP::afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (cost++ % G.V() == 0)
        findNegativeCycle();
}

void algs4::BellmanFordSP::findNegativeCycle() {
    int V = edgeTo.size();
    EdgeWeightedDigraph spt(V);
    for (int v = 0; v < V; ++v) {
        if (edgeTo[v])
            spt.addEdge(*edgeTo[v]);
    }
    DirectedCycle cf(spt);
    cycle = cf.cycle();
}

algs4::BellmanFordSP::BellmanFordSP(const EdgeWeightedDigraph &G, int s) : SP(G, s), onQ(G.V()) {
    queue.push_back(s);
    onQ[s] = true;
    while (!queue.empty() && !hasNegativeCycle()) {
        int v = queue.front();
        queue.pop_front();
        onQ[v] = false;
        relax(G, v);
    }
}
