#ifndef ALGS4_BELLMANFORDSP_HPP
#define ALGS4_BELLMANFORDSP_HPP

#include <queue>
#include <vector>

#include "DirectedCycle.hpp"
#include "SP.hpp"

namespace algs4 {
    class BellmanFordSP : public SP {
    private:
        std::vector<bool> onQ_;           // Is this vertex on the queue?
        std::queue<int> queue_;           // vertices being relaxed
        int cost_ = 0;                    // number of calls to relax()
        std::vector<DirectedEdge> cycle_; // negative cycle in edgeTo_[]?

        void onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;
        void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;
        void findNegativeCycle();

    public:
        BellmanFordSP(const EdgeWeightedDigraph &G, int s);

        bool hasNegativeCycle() const { return !cycle_.empty(); }
        std::vector<DirectedEdge> negativeCycle() const { return cycle_; }
    };
}

inline void algs4::BellmanFordSP::onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (!onQ_[w]) {
        queue_.push(w);
        onQ_[w] = true;
    }
}

inline void algs4::BellmanFordSP::afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (cost_++ % G.V() == 0)
        findNegativeCycle();
}

inline void algs4::BellmanFordSP::findNegativeCycle() {
    int V = static_cast<int>(std::ssize(edgeTo_));
    EdgeWeightedDigraph spt(V);
    for (int v = 0; v < V; ++v) {
        if (edgeTo_[v])
            spt.addEdge(edgeTo_[v]);
    }
    DirectedCycle cf(spt);
    auto c = cf.cycle();
    cycle_ = {c.begin(), c.end()};
}

inline algs4::BellmanFordSP::BellmanFordSP(const EdgeWeightedDigraph &G, int s) : SP(G, s), onQ_(G.V()) {
    queue_.push(s);
    onQ_[s] = true;
    while (!queue_.empty() && !hasNegativeCycle()) {
        int v = queue_.front();
        queue_.pop();
        onQ_[v] = false;
        relax(G, v);
    }
}

#endif // ALGS4_BELLMANFORDSP_HPP
