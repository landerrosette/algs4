#ifndef ALGS4_DIJKSTRASP_HPP
#define ALGS4_DIJKSTRASP_HPP


#include "IndexMinPQ.hpp"
#include "SP.hpp"

namespace algs4 {
    class DijkstraSP : public SP {
    private:
        IndexMinPQ<double> pq_;

        constexpr void onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

    public:
        constexpr DijkstraSP(const EdgeWeightedDigraph &G, int s);
    };
}

constexpr void algs4::DijkstraSP::onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (pq_.contains(w)) pq_.change(w, distTo_[w]);
    else pq_.insert(w, distTo_[w]);
}

constexpr algs4::DijkstraSP::DijkstraSP(const EdgeWeightedDigraph &G, int s) : SP(G, s), pq_(G.V()) {
    pq_.insert(s, 0.0);
    while (!pq_.isEmpty())
        relax(G, static_cast<int>(pq_.delMin()));
}


#endif //ALGS4_DIJKSTRASP_HPP
