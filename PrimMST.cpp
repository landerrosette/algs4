#include "PrimMST.h"
#include <limits>

void PrimMST::visit(const EdgeWeightedGraph &G, int v) {
    marked[v] = true;
    for (const auto &e: G.adj(v)) {
        int w = e.other(v);
        if (marked[w]) continue; // v-w is ineligible
        if (e.weight() < distTo[w]) {
            edgeTo[w] = e;
            distTo[w] = e.weight();
            if (pq.contains(w)) pq.change(w, distTo[w]);
            else pq.insert(w, distTo[w]);
        } // Edge e is new best connection from tree to w.
    }
}

PrimMST::PrimMST(const EdgeWeightedGraph &G) : edgeTo(G.V()), distTo(G.V(), std::numeric_limits<double>::infinity()),
                                               marked(G.V()), pq(G.V()) {
    distTo[0] = 0.0;
    pq.insert(0, 0.0);
    while (!pq.isEmpty()) visit(G, *pq.delMin());
}

std::list<Edge> PrimMST::edges() const {
    std::list<Edge> mst;
    for (int v = 1; v < edgeTo.size(); ++v) mst.push_front(*edgeTo[v]);
    return mst;
}
