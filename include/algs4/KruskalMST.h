#ifndef ALGS4_KRUSKALMST_H
#define ALGS4_KRUSKALMST_H


#include <list>

#include "EdgeWeightedGraph.h"
#include "MinPQ.h"
#include "MST.h"
#include "UF.h"

namespace algs4 {
    class KruskalMST : public MST {
    private:
        std::list<Edge> mst;

    public:
        explicit KruskalMST(const EdgeWeightedGraph &G);

        std::list<Edge> edges() const override { return mst; }
    };
}

inline algs4::KruskalMST::KruskalMST(const EdgeWeightedGraph &G) {
    MinPQ<Edge> pq(G.E());
    for (const auto &e: G.edges())
        pq.insert(e);
    UF uf(G.V());
    while (!pq.isEmpty() && mst.size() < G.V() - 1) {
        auto e = pq.delMin();
        int v = e->either(), w = e->other(v);
        if (uf.connected(v, w)) continue;
        uf.unionize(v, w);
        mst.push_back(*e);
    }
}


#endif //ALGS4_KRUSKALMST_H
