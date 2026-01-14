#ifndef ALGS4_PRIMMST_HPP
#define ALGS4_PRIMMST_HPP


#include <algorithm>
#include <limits>
#include <vector>

#include "EdgeWeightedGraph.hpp"
#include "IndexMinPQ.hpp"
#include "MST.hpp"

namespace algs4 {
    class PrimMST : public MST {
    private:
        std::vector<Edge> edgeTo;   // shortest edge from tree vertex
        std::vector<double> distTo; // distTo[w] = edgeTo[w].weight()
        std::vector<bool> marked;   // true if v on tree
        IndexMinPQ<double> pq;      // eligible crossing edges

        void visit(const EdgeWeightedGraph &G, int v);

    public:
        explicit PrimMST(const EdgeWeightedGraph &G);

        std::vector<Edge> edges() const override;
    };
}

inline void algs4::PrimMST::visit(const EdgeWeightedGraph &G, int v) {
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

inline algs4::PrimMST::PrimMST(const EdgeWeightedGraph &G)
    : edgeTo(G.V()), distTo(G.V(), std::numeric_limits<double>::infinity()), marked(G.V()), pq(G.V()) {
    distTo[0] = 0.0;
    pq.insert(0, 0.0);
    while (!pq.isEmpty())
        visit(G, static_cast<int>(pq.delMin()));
}

inline std::vector<algs4::Edge> algs4::PrimMST::edges() const {
    std::vector<Edge> mst;
    for (int v = 1; v < std::ssize(edgeTo); ++v)
        mst.push_back(edgeTo[v]);
    std::ranges::reverse(mst);
    return mst;
}


#endif //ALGS4_PRIMMST_HPP
