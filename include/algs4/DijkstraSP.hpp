#ifndef ALGS4_DIJKSTRASP_HPP
#define ALGS4_DIJKSTRASP_HPP


#include "IndexMinPQ.hpp"
#include "SP.hpp"

namespace algs4 {
    class DijkstraSP : public SP {
    private:
        IndexMinPQ<double> pq;

        constexpr void onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

    public:
        constexpr DijkstraSP(const EdgeWeightedDigraph &G, int s);
    };
}

constexpr void algs4::DijkstraSP::onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (pq.contains(w)) pq.change(w, distTo_[w]);
    else pq.insert(w, distTo_[w]);
}

constexpr algs4::DijkstraSP::DijkstraSP(const EdgeWeightedDigraph &G, int s) : SP(G, s), pq(G.V()) {
    pq.insert(s, 0.0);
    while (!pq.isEmpty())
        relax(G, static_cast<int>(pq.delMin()));
}


#endif //ALGS4_DIJKSTRASP_HPP
