#ifndef ALGS4_DIJKSTRASP_H
#define ALGS4_DIJKSTRASP_H


#include "IndexMinPQ.h"
#include "SP.h"

class DijkstraSP : public SP {
private:
    IndexMinPQ<double> pq;

    void onRelaxationSuccess(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

public:
    DijkstraSP(const EdgeWeightedDigraph &G, int s);
};


#endif //ALGS4_DIJKSTRASP_H