#include "KruskalMST.h"
#include "MinPQ.h"
#include "UF.h"

KruskalMST::KruskalMST(const EdgeWeightedGraph &G) {
    MinPQ<Edge> pq(G.E());
    for (const auto &e: G.edges()) pq.insert(e);
    UF uf(G.V());
    while (!pq.isEmpty() && mst.size() < G.V() - 1) {
        auto e = pq.delMin();
        int v = e->either(), w = e->other(v);
        if (uf.connected(v, w)) continue;
        uf.unionize(v, w);
        mst.push_back(*e);
    }
}

std::list<Edge> KruskalMST::edges() const {
    return mst;
}
