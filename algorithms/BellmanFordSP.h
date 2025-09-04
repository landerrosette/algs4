#ifndef ALGS4_BELLMANFORDSP_H
#define ALGS4_BELLMANFORDSP_H


#include <list>
#include <vector>

#include "SP.h"

class BellmanFordSP : public SP {
private:
    std::vector<bool> onQ;         // Is this vertex on the queue?
    std::list<int> queue;          // vertices being relaxed
    int cost = 0;                  // number of calls to relax()
    std::list<DirectedEdge> cycle; // negative cycle in edgeTo[]?

    void onRelaxationSuccess(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

    void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

    void findNegativeCycle();

public:
    BellmanFordSP(const EdgeWeightedDigraph &G, int s);

    bool hasNegativeCycle() const { return !cycle.empty(); }

    std::list<DirectedEdge> negativeCycle() const { return cycle; }
};


#endif //ALGS4_BELLMANFORDSP_H
