#include "DijkstraSP.h"

void DijkstraSP::onRelax(const DirectedEdge& e, int w) {
    if (pq.contains(w)) pq.change(w, distTo_[w]);
    else pq.insert(w, distTo_[w]);
}

DijkstraSP::DijkstraSP(const EdgeWeightedDigraph& G, int s) : SP(G, s), pq(G.V()) {
    pq.insert(s, 0.0);
    while (!pq.isEmpty()) relax(G, *pq.delMin());
}
